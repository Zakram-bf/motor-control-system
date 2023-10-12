
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _INIT ProgramInit(void)
{
	fb_motor.dt = 0.01;
	fb_motor.ke = 0.24;
	fb_motor.Tm = 0.1;
	fb_motor.u = 0;
	fb_motor.integrator.dt = 0.01;
	
	fb_motor2.dt = 0.01;
	fb_motor2.ke = 0.48;
	fb_motor2.Tm = 0.05;
	fb_motor2.u = 0;
	fb_motor2.integrator.dt = 0.01;
	
	fb_controller.dt = 0.01;
	fb_controller.integrator.dt = 0.01;
	fb_controller.k_i = 14.4;
	fb_controller.k_p = 0.72;
	fb_controller.max_abs_value = 24.0;
	
	speed = 0;
	counter = 0;
}

void _CYCLIC ProgramCyclic(void)
{
	if (enable)
	{
		if (counter == 100)
		{
			speed = 50;
		}
		else if (counter == 250)
		{
			speed = 0;
			counter = 0;
		}
		counter++;
		
		fb_controller.e = speed - fb_motor.w;
		FB_Controller(&fb_controller);
		
		fb_motor.u = fb_controller.u;
		
		//fb_motor.u = speed * fb_motor.ke;
		
		fb_motor2.u = fb_controller.u;
		//fb_motor2.u = speed * fb_motor2.ke;
		
		FB_Motor(&fb_motor);
		FB_Motor(&fb_motor2);
		
	}
}

void _EXIT ProgramExit(void)
{

}

