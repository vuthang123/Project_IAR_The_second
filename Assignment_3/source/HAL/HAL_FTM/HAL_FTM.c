#include "HAL_FTM.h"
#include "string.h"
#include "HAL_CLOCK.h"
#include "stdbool.h"	
#define    kFTM_CntMax      (1U << 8)
#define    kFTM_CntMin      (1U << 9)
#define kFTM_FaultInterruptEnable   (1U << 8)
#define PCC_CLKCFG_CGC_MASK                      (0x40000000U)



static void FTM_SetPwmSync(FTM_Type *base, uint32_t syncMethod, bool swRstCnt);

static void FTM_SetReloadPoints(FTM_Type *base, uint32_t reloadPoints);

Status FTM_Init(FTM_Type *FTM_0 , const ftm_config_t *config)
{
	 /*eNABLE CLOCK PCC_FLEXTMR0 */
	PCC2->CLKCFG[PCC_FLEXTMR0_INDEX] |= PCC_CLKCFG_CGC_MASK;
	 /*DISABLE PROTECT */
	 /* Configure the fault mode, enable FTM mode and disable write protection */
    FTM_0->MODE = (FTM_0->MODE & (~FTM_MODE_FAULTIE_MASK)) | FTM_MODE_FTMEN_MASK | FTM_MODE_WPDIS_MASK;
	
    /* Configure the update mechanism for buffered registers */
    FTM_SetPwmSync(FTM_0, config->pwmSyncMode, config->swTriggerResetCount);
	/* Setup intermediate register reload points */
    FTM_SetReloadPoints(FTM_0, config->reloadPoints);
	
	/* Set the clock prescale factor */
    FTM_0->SC = FTM_SC_PS(config->prescale);

    /* Setup the counter operation */
    FTM_0->CONF = (FTM_CONF_BDMMODE(config->bdmMode) | FTM_CONF_GTBEEN(config->useGlobalTimeBase));

    /* Initial state of channel output */
    FTM_0->OUTINIT = config->chnlInitState;

    /* Channel polvarity */
    FTM_0->POL = config->chnlPolarity;

    /* Set the external trigger sources */
    FTM_0->EXTTRIG = config->extTriggers;
	
	FTM_0->CONF &= ~FTM_CONF_ITRIGR_MASK;
	
    /* FTM fault filter value */
   
    FTM_0->FLTCTRL &= ~FTM_FLTCTRL_FFVAL_MASK;
    FTM_0->FLTCTRL |= FTM_FLTCTRL_FFVAL(config->faultFilterValue);	
	
	return kStatus_Success; 
}

static void FTM_SetPwmSync(FTM_Type *base, uint32_t syncMethod, bool swRstCnt)
{
    uint8_t chnlNumber = 0;

    /* Enable PWM synchronization of output mask register */
    base->SYNC |= FTM_SYNC_SYNCHOM_MASK;
	
    for (chnlNumber = 0; chnlNumber < ((uint8_t)FSL_FEATURE_FTM_CHANNEL_COUNTn(base) / 2U); chnlNumber++)
    {
        /* Enable PWM synchronization of registers C(n)V and C(n+1)V */
        base->COMBINE |= (1UL << (FTM_COMBINE_SYNCEN0_SHIFT + (FTM_COMBINE_COMBINE1_SHIFT * chnlNumber)));
    }
    
    /* Use enhanced PWM synchronization method. Use PWM sync to update register values */
    base->SYNCONF |= (FTM_SYNCONF_SYNCMODE_MASK | FTM_SYNCONF_CNTINC_MASK | FTM_SYNCONF_INVC_MASK | FTM_SYNCONF_SWOC_MASK);

    if ((syncMethod & FTM_SYNC_SWSYNC_MASK) != 0U)
    {
        /* Enable needed bits for software trigger to update registers with its buffer value */
        base->SYNCONF  |= (FTM_SYNCONF_SWWRBUF_MASK | FTM_SYNCONF_SWINVC_MASK | FTM_SYNCONF_SWSOC_MASK | FTM_SYNCONF_SWOM_MASK);
        /* Enable software trigger synchronization count. */
        if (swRstCnt)
        {
            base->SYNCONF  |= FTM_SYNCONF_SWRSTCNT_MASK;
        }
    }
}

static void FTM_SetReloadPoints(FTM_Type *base, uint32_t reloadPoints)
{
    uint32_t chnlNumber = 0;
    int8_t chnlCount    = FSL_FEATURE_FTM_CHANNEL_COUNTn(base);

    /* Need CNTINC bit to be 1 for CNTIN register to update with its buffer value on reload  */
    base->SYNCONF |= FTM_SYNCONF_CNTINC_MASK;

    for (chnlNumber = 0; chnlNumber < ((uint32_t)chnlCount / 2U); chnlNumber++)
    {
        /* Need SYNCEN bit to be 1 for CnV reg to update with its buffer value on reload  */
        base->COMBINE |= (1UL << (FTM_COMBINE_SYNCEN0_SHIFT + (FTM_COMBINE_COMBINE1_SHIFT * chnlNumber)));
    }

    /* Enable the selected channel match reload points */
    base->PWMLOAD &= ~((1UL << (uint32_t)chnlCount) - 1U);
    base->PWMLOAD |= (reloadPoints & ((1UL << (uint32_t)chnlCount) - 1U));
    base->PWMLOAD &= ~FTM_PWMLOAD_HCSEL_MASK;

    /* These reload points are used when counter is in up-down counting mode */
    if ((reloadPoints & (uint32_t)kFTM_CntMax) != 0U)
    {
        /* Reload when counter turns from up to down */
        base->SYNC |= FTM_SYNC_CNTMAX_MASK;
    }
    else
    {
        base->SYNC &= ~FTM_SYNC_CNTMAX_MASK;
    }

    if ((reloadPoints & (uint32_t)kFTM_CntMin) != 0U)
    {
        /* Reload when counter turns from down to up */
        base->SYNC |= FTM_SYNC_CNTMIN_MASK;
    }
    else
    {
        base->SYNC &= ~FTM_SYNC_CNTMIN_MASK;
    }
}

static inline void FTM_SetPwmOutputEnable(FTM_Type *base, ftm_chnl_t chnlNumber, bool value)
{
    if (value)
    {
        base->SC |= (1UL << ((uint32_t)chnlNumber + FTM_SC_PWMEN0_SHIFT));
    }
    else
    {
        base->SC &= ~(1UL << ((uint32_t)chnlNumber + FTM_SC_PWMEN0_SHIFT));
    }
}

/*!
 * brief Configures the PWM signal parameters.
 *
 * Call this function to configure the PWM signal period, mode, duty cycle, and edge. Use this
 * function to configure all FTM channels that are used to output a PWM signal.
 *
 * param base        FTM peripheral base address
 * param chnlParams  Array of PWM channel parameters to configure the channel(s)
 * param numOfChnls  Number of channels to configure; This should be the size of the array passed in
 * param mode        PWM operation mode, options available in enumeration ::ftm_pwm_mode_t
 * param pwmFreq_Hz  PWM signal frequency in Hz
 * param srcClock_Hz FTM counter clock in Hz
 *
 * return kStatus_Success if the PWM setup was successful
 *         kStatus_Error on failure
 */
uint32_t  FTM_SetupPwm(FTM_Type *base,
                      const ftm_chnl_pwm_signal_param_t *chnlParams,
                      uint8_t numOfChnls,
                      ftm_pwm_mode_t mode,
                      uint32_t pwmFreq_Hz,
                      uint32_t srcClock_Hz)

{
    
    uint32_t mod, reg;
    uint32_t ftmClock;
    uint32_t cnv;
    uint8_t i;
	
    ftmClock = (srcClock_Hz / (1UL << (base->SC & FTM_SC_PS_MASK)));
	
    if (mode == kFTM_CenterAlignedPwm)
    {
        base->SC |= FTM_SC_CPWMS_MASK;
        mod = ftmClock / (pwmFreq_Hz * 2U);
    }
    else
    {
        base->SC &= ~FTM_SC_CPWMS_MASK;
        mod = (ftmClock / pwmFreq_Hz) - 1U;
    }

    /* Set the PWM period */
    base->CNTIN = 0U;
    base->MOD   = mod;

    /* Setup each FTM channel */
    for (i = 0; i < numOfChnls; i++)
    {
        /* Return error if requested dutycycle is greater than the max allowed */
        if (chnlParams->dutyCyclePercent > 100U)
        {
            return kStatus_OutOfRange;
        }

        if (chnlParams->dutyCyclePercent == 100U)
        {
            /* For 100% duty cycle */
            cnv = mod + 1U;
        }
        else
        {
            cnv = (mod * chnlParams->dutyCyclePercent) / 100U;
        }

        if ((mode == kFTM_EdgeAlignedPwm) || (mode == kFTM_CenterAlignedPwm))
        {
            /* Clear the current mode and edge level bits */
            reg = base->CONTROLS[chnlParams->chnlNumber].CnSC;
            reg &= ~(FTM_CnSC_MSA_MASK | FTM_CnSC_MSB_MASK | FTM_CnSC_ELSA_MASK | FTM_CnSC_ELSB_MASK);

            /* Setup the active level */
            reg |= (uint32_t)chnlParams->level << FTM_CnSC_ELSA_SHIFT;

            /* Edge-aligned mode needs MSB to be 1, don't care for Center-aligned mode */
            reg |= FTM_CnSC_MSB(1U);

            /* Update the mode and edge level */
            base->CONTROLS[chnlParams->chnlNumber].CnSC = reg;

            base->CONTROLS[chnlParams->chnlNumber].CnV = cnv;

            /* Set to output mode */
            FTM_SetPwmOutputEnable(base, chnlParams->chnlNumber, true);

        }
        chnlParams++;
    }

    return kStatus_Success;
}

/*!
 * brief Enables the selected FTM interrupts.
 *
 * param base FTM peripheral base address
 * param mask The interrupts to enable. This is a logical OR of members of the
 *             enumeration ::ftm_interrupt_enable_t
 */
void FTM_EnableInterrupts(FTM_Type *base, uint32_t mask)
{
    uint32_t chnlInts  = (mask & 0xFFU);
    uint8_t chnlNumber = 0;

    /* Enable the fault interrupt */
    if ((mask & (uint32_t)kFTM_FaultInterruptEnable) != 0U)
    {
        base->MODE |= FTM_MODE_FAULTIE_MASK;
    }

    /* Enable the channel interrupts ch3*/
    while (chnlInts != 0U)
    {
        if ((chnlInts & 0x1U) != 0U)
        {
            base->CONTROLS[chnlNumber].CnSC |= FTM_CnSC_CHIE_MASK;
        }
        chnlNumber++;
        chnlInts = chnlInts >> 1U;
    }
	
}
/*!
 * @brief Starts the FTM counter.
 *
 * @param base        FTM peripheral base address
 * @param clockSource FTM clock source; After the clock source is set, the counter starts running.
 */
void FTM_StartTimer(FTM_Type *base, ftm_clock_source_t clockSource)
{

    base->SC &= ~(FTM_SC_CLKS_MASK);
    base->SC |= FTM_SC_CLKS(clockSource);
}
/*!
 * brief Disables the selected FTM interrupts.
 *
 * param base FTM peripheral base address
 * param mask The interrupts to enable. This is a logical OR of members of the
 *             enumeration ::ftm_interrupt_enable_t
 */
void FTM_DisableInterrupts(FTM_Type *base, uint32_t mask)
{
    uint32_t chnlInts  = (mask & 0xFFU);
    uint8_t chnlNumber = 0;

    /* Disable the channel interrupts */
    while (chnlInts != 0U)
    {
        if ((chnlInts & 0x01U) != 0U)
        {
            base->CONTROLS[chnlNumber].CnSC &= ~FTM_CnSC_CHIE_MASK;
        }
        chnlNumber++;
        chnlInts = chnlInts >> 1U;
    }
}
/*!
 * brief Updates the duty cycle of an active PWM signal.
 *
 * param base              FTM peripheral base address
 * param chnlNumber        The channel/channel pair number. In combined mode, this represents
 *                          the channel pair number
 * param currentPwmMode    The current PWM mode set during PWM setup
 * param dutyCyclePercent  New PWM pulse width; The value should be between 0 to 100
 *                          0=inactive signal(0% duty cycle)...
 *                          100=active signal (100% duty cycle)
 * return kStatus_Success if the PWM update was successful
 *         kStatus_Error on failure
 */
uint32_t FTM_UpdatePwmDutycycle(FTM_Type *base,
                                ftm_chnl_t chnlNumber,
                                ftm_pwm_mode_t currentPwmMode,
                                uint8_t dutyCyclePercent)
{
    uint32_t cnv;

    if (dutyCyclePercent == 100U)
    {
        /* For 100% duty cycle */
        cnv =  base->MOD + 1U;
    }
    else
    {
        cnv = ( base->MOD * dutyCyclePercent) / 100U;
    }

    if ((currentPwmMode == kFTM_EdgeAlignedPwm) || (currentPwmMode == kFTM_CenterAlignedPwm))
    {
        base->CONTROLS[chnlNumber].CnV = cnv;
    }
    
    return kStatus_Success;
}

/*!
 * @brief Enables or disables the FTM software trigger for PWM synchronization.
 *
 * @param base   FTM peripheral base address
 * @param enable true: software trigger is selected, false: software trigger is not selected
 */
void FTM_SetSoftwareTrigger(FTM_Type *base, bool enable)
{
    if (enable)
    {
        base->SYNC |= FTM_SYNC_SWSYNC_MASK;
    }
    else
    {
        base->SYNC &= ~FTM_SYNC_SWSYNC_MASK;
    }
}
/*!
 * brief Updates the edge level selection for a channel.
 *
 * param base       FTM peripheral base address
 * param chnlNumber The channel number
 * param level      The level to be set to the ELSnB:ELSnA field; Valid values are 00, 01, 10, 11.
 *                   See the Kinetis SoC reference manual for details about this field.
 */
void FTM_UpdateChnlEdgeLevelSelect(FTM_Type *base, ftm_chnl_t chnlNumber, uint8_t level)
{
    /* Clear the field and write the new level value */
    base->CONTROLS[chnlNumber].CnSC &= ~(FTM_CnSC_ELSA_MASK | FTM_CnSC_ELSB_MASK);
    base->CONTROLS[chnlNumber].CnSC |= ((uint32_t)level << FTM_CnSC_ELSA_SHIFT) & (FTM_CnSC_ELSA_MASK | FTM_CnSC_ELSB_MASK);
}

