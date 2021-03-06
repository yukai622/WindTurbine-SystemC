#include "systemc-ams.h"
#include "imperial_defs.h"

SC_MODULE (mechanical_lsf)
{
  sc_out<double> Wm, Wmi, Wgi, theta; // mechanical angular speed 
  sca_tdf::sca_out<double> Wg; // generator angular speed 
  sc_in<double> ddtWm, ddtWg; // first derivative of Wm, Wg
  sca_lsf::sca_signal inDdtWm, inDdtWg, idtWm, idtWg, sumW, thetaSig,tempWm2; 
  
  sca_lsf::sca_de::sca_source * ddtWm_lsf, * ddtWg_lsf; // convert to LSF domain
  sca_lsf::sca_integ * wmInteg, * wgInteg, * thetaInteg; 
  sca_lsf::sca_de::sca_sink * outWm, * outWmi, * outWgi, * outTheta;
  sca_lsf::sca_tdf::sca_sink * outWg;
  sca_lsf::sca_sub * addW; 
  
  SC_CTOR(mechanical_lsf): Wm("Wm"), Wg("Wg"), Wmi("Wmi"), Wgi("Wgi"), theta("theta"), ddtWm("ddtWm"), ddtWg("ddtWg"){
    
    ddtWm_lsf = new sca_lsf::sca_de::sca_source("ddtWm_lsf", 1); 
    ddtWm_lsf->inp(ddtWm); 
    ddtWm_lsf->y(inDdtWm); 
    ddtWm_lsf->set_timestep(TIMESTEP);
    
    wmInteg = new sca_lsf::sca_integ("wmInteg", 1, 2.100001);  
    wmInteg->x(inDdtWm); 
    wmInteg->y(idtWm); 
    wmInteg->set_timestep(TIMESTEP);
    
    outWm = new sca_lsf::sca_de::sca_sink("outWm"); 
    outWm->x(idtWm);
    outWm->outp(Wm); 
    outWm->set_timestep(TIMESTEP);

    outWmi = new sca_lsf::sca_de::sca_sink("outWmi"); 
    outWmi->x(idtWm);
    outWmi->outp(Wmi); 
    outWmi->set_timestep(TIMESTEP);
    
    ddtWg_lsf = new sca_lsf::sca_de::sca_source("ddtWg_lsf"); 
    ddtWg_lsf->inp(ddtWg); 
    ddtWg_lsf->y(inDdtWg); 
    ddtWg_lsf->set_timestep(TIMESTEP);
    
    wgInteg = new sca_lsf::sca_integ("wgInteg", 1, 2.2192116114);  
    wgInteg->x(inDdtWg); 
    wgInteg->y(idtWg); 
    wgInteg->set_timestep(TIMESTEP);

    outWg = new sca_lsf::sca_tdf::sca_sink("outWg"); 
    outWg->x(idtWg);
    outWg->outp(Wg); 
    outWg->set_timestep(TIMESTEP);
    
    outWgi = new sca_lsf::sca_de::sca_sink("outWgi"); 
    outWgi->x(idtWg);
    outWgi->outp(Wgi); 
    outWgi->set_timestep(TIMESTEP);

    addW = new sca_lsf::sca_sub("addW"); 
    addW->x1(idtWg); 
    addW->x2(idtWm); 
    addW->y(sumW); 
    addW->set_timestep(TIMESTEP);
    
    thetaInteg = new sca_lsf::sca_integ("thetaInteg", 1, 1.000268);  
    thetaInteg->x(sumW); 
    thetaInteg->y(thetaSig); 
    thetaInteg->set_timestep(TIMESTEP);
    
    outTheta = new sca_lsf::sca_de::sca_sink("outTheta"); 
    outTheta->x(thetaSig);
    outTheta->outp(theta);
    outTheta->set_timestep(TIMESTEP);
    
  }

}; 
