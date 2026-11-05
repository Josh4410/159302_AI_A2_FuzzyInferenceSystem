#include <algorithm>
#include "fuzzylogic.h"

/////////////////////////////////////////////////////////////////
//Initialise Fuzzy Rules

void initFuzzyRules(fuzzy_system_rec *fl) {
	
   const int
      no_of_x_rules = 25,
      no_of_theta_rules = 25;
   
   // Lecture FAMM
   static const int famm[5][5] = {
      {out_nl,out_nm, out_ns, out_ze, out_ps},
      {out_nl, out_nm, out_ns,out_ps, out_pm},
      {out_nm, out_ns, out_ze, out_ps, out_pm},
      {out_nm, out_ns, out_ps, out_pm, out_pl},
      {out_ns, out_ze, out_ps, out_pm, out_pl}
   };

   int i;
   for(int j = 0; j < 5; j++){
      for(i=0; i<5;i++){
         //(*fl).rules[i].inp_index[0] = in_angle; // lecture alternative
         int rule = j * 5 + i;

         fl->rules[rule].inp_index[0] = INPUT_X;
         fl->rules[rule].inp_fuzzy_set[1] = j;
         fl->rules[rule].inp_fuzzy_set[0] = i;
         fl->rules[rule].inp_index[1] = INPUT_Y;
         fl->rules[rule].out_fuzzy_set = famm[j][i];
         //define remaining rules

   }}
	
//---------------------------------------------------------------------------- 	
//THETA vs. THETA_DOT	
//  50 non yamakawa setup
/* 
   for (i = 0;i < no_of_theta_rules;i++) {
       fl->rules[i].inp_index[0] = in_theta;
       fl->rules[i].inp_index[1] = in_theta_dot;
   }
  */    
   /* Regions for theta and theta_dot: */
   //sample only
   // fl->rules[0].inp_fuzzy_set[0] = in_nl;
   // fl->rules[0].inp_fuzzy_set[1] = in_nl;
   
	
	
//----------------------------------------------------------------------------   
//X vs. X_DOT
// 
/*
   for (i = 0;i < no_of_x_rules;i++) {
   	  fl->rules[i + no_of_theta_rules].inp_index[0] = in_x;
   	  fl->rules[i + no_of_theta_rules].inp_index[1] = in_x_dot;
	}
	  */
	/* Regions for x and x_dot: */
   //sample only
   // fl->rules[25+0].inp_fuzzy_set[0] = in_nl;
   // fl->rules[25+0].inp_fuzzy_set[1] = in_nl;
   
   //and so on, and so forth...

   // fl->rules[25+24].out_fuzzy_set = out_nl;
      return;
}


void initMembershipFunctions(fuzzy_system_rec *fl) {
   /* The X membership functions */
   fl->inp_mem_fns[INPUT_X][in_nl] = init_trapz(-0.30f, 0.0f, 0.0f, 0.0f, left_trapezoid); // crunching the trapezoids down like this makes it switch between quckily and not as smooth,
   fl->inp_mem_fns[INPUT_X][in_ns] = init_trapz(-0.3f, -0.1f, -0.1f, 0.0f, regular_trapezoid); // more reactive but starts oscillating, trying to get it to react sooner to the edge cases +60
   
   fl->inp_mem_fns[INPUT_X][in_ze] = init_trapz(-0.1f, -0.0f, 0.0f, 0.1f, regular_trapezoid); //0, 0 to make a triangle
   
   fl->inp_mem_fns[INPUT_X][in_ps] = init_trapz(0.0f, 0.1f, 0.1f, 0.3f, regular_trapezoid);
   fl->inp_mem_fns[INPUT_X][in_pl] = init_trapz(0.0f, 0.3f, 0.0f, 0.0f, right_trapezoid);


   /* The Y membership functions */
   fl->inp_mem_fns[INPUT_Y][in_nl] = init_trapz(-0.30f, -0.0f, 0.0f, 0.0f, left_trapezoid);
   fl->inp_mem_fns[INPUT_Y][in_ns] = init_trapz(-0.3f, -0.1f, -0.1f, 0.0f, regular_trapezoid);
   
   fl->inp_mem_fns[INPUT_Y][in_ze] = init_trapz(-0.3f, -0.0f, 0.0f, 0.3f, regular_trapezoid); //0, 0 to make a triangle
   
   fl->inp_mem_fns[INPUT_Y][in_ps] = init_trapz(0.0f, 0.1f, 0.1f, 0.3f, regular_trapezoid);
   fl->inp_mem_fns[INPUT_Y][in_pl] = init_trapz(0.0f, 0.3f, 0.0f, 0.0f, right_trapezoid);


   
/*The X membership functions *//*
   fl->inp_mem_fns[INPUT_X][in_nl] = init_trapz(-1.50f, -1.0f, 0.0f, 0.0f, left_trapezoid);
   fl->inp_mem_fns[INPUT_X][in_ns] = init_trapz(-1.5f, -1.0f, -0.6f, 0.0f, regular_trapezoid);
   fl->inp_mem_fns[INPUT_X][in_ze] = init_trapz(-0.6f, -0.0f, 0.0f, 0.6f, regular_trapezoid); //0, 0 to make a triangle
   fl->inp_mem_fns[INPUT_X][in_ps] = init_trapz(0.0f, 0.6f, 1.0f, 1.50f, regular_trapezoid);
   fl->inp_mem_fns[INPUT_X][in_pl] = init_trapz(1.0f, 1.25f, 0.0f, 0.0f, right_trapezoid);

/*The Y membership functions
   fl->inp_mem_fns[INPUT_Y][in_nl] = init_trapz(-1.50f, -1.0f, 0.0f, 0.0f, left_trapezoid);
   fl->inp_mem_fns[INPUT_Y][in_ns] = init_trapz(-1.5f, -1.0f, -0.6f, 0.0f, regular_trapezoid);
   fl->inp_mem_fns[INPUT_Y][in_ze] = init_trapz(-0.6f, -0.0f, 0.0f, 0.6f, regular_trapezoid);
   fl->inp_mem_fns[INPUT_Y][in_ps] = init_trapz(0.0f, 0.6f, 1.0f, 1.5f, regular_trapezoid);
   fl->inp_mem_fns[INPUT_Y][in_pl] = init_trapz(1.0f, 1.5f, 0.0f, 0.0f, right_trapezoid);
*/

   //Sample routines only, to give you an idea of what to do here
  	//~ fl->inp_mem_fns[in_x][in_neg] = init_trapz (-1.5,-0.5,0,0,left_trapezoid);
   //~ fl->inp_mem_fns[in_x][in_ze] = init_trapz (-1.5,-0.5,0.5,1.5,regular_trapezoid);
   //~ fl->inp_mem_fns[in_x][in_pos] = init_trapz (0.5,1.5,0,0,right_trapezoid);
	
   //angle
	//fl->inp_mem_fns[in_angle][in_negatively_large] = init_trapz(14.0f, 20.0f, 0.0f, 0.0f, left_trapezoid);
	//fl->inp_mem_fns[in_angle][in_negatively_medium] = inti_trapz(14.0f,20.0f, 34.0v, 40.0f, regular_trapezoid);
	//fl->inp_mem_fns[in_angle][in_positively_large] = init_trapz(34.0f,40.0f,0.0f,0.0f, right_trapezoid);

   /* The X dot membership functions */
   //enter the appropriate membership function initialisations here 

   /* The theta membership functions */
   //enter the appropriate membership function initialisations here
  	
   /* The theta dot membership functions */
   //enter the appropriate membership function initialisations here
  	

	
	
   return;
}

void initFuzzySystem (fuzzy_system_rec *fl) {

   //Note: The settings of these parameters will depend upon your fuzzy system design
   fl->no_of_inputs = 2;  /* Inputs are handled 2 at a time only */
   fl->no_of_rules = 25; //num of rules was 50 // old ver/ not yamakawa
   fl->no_of_inp_regions = 5; // number of fuzzy sets per input
   fl->no_of_outputs = 7; //was8 //was 9
	
   
   
   
   coefficient_A=0.8; // 0.8; //1.2;  // 2.5; //3.0; //1
   coefficient_B=0.08; ///0.1; //0.3; //0.1 // was 1.0 
   coefficient_C=0.13; //0.5;  //0.2; //0.03 //
   coefficient_D=0.12; //0.15; //0.3; //0.1

   //
   fl->output_values[out_nl] = -950.0; // -600.0;
   fl->output_values[out_nm] = -260.0; // -240.0;
   fl->output_values[out_ns] = -240.0; // -120.0;

   fl->output_values[out_ze] = 0.0;

   fl->output_values[out_ps] = 240.0; // 120.0;
   fl->output_values[out_pm] = 260.0; // 240.0;
   fl->output_values[out_pl] = 950.0; // 600.0;

	



	// Sample only
	// fl->output_values [out_nvl]=-95.0;
	// fl->output_values [out_nl] = -85.0;
   /*
   fl->output_values[out_small_push_left]= -15f; //-15 Newtons
	fl->output_values[out_large_push_left] = -100f; //-100 Netwons
	fl->rules = new rule[fl->no_of_rules]; // allocate memory for the rules
   */
   

   fl->rules = (rule *) malloc ((size_t)(fl->no_of_rules*sizeof(rule)));
   
   fl->allocated = true;
   
   initFuzzyRules(fl);
   initMembershipFunctions(fl);
   return;
}

//////////////////////////////////////////////////////////////////////////////

trapezoid init_trapz (float x1,float x2,float x3,float x4, trapz_type typ) {
	
   trapezoid trz;
   trz.a = x1;
   trz.b = x2;
   trz.c = x3;
   trz.d = x4;
   trz.tp = typ;
   switch (trz.tp) {
	   
      case regular_trapezoid:
         	 trz.l_slope = 1.0/(trz.b - trz.a);
         	 trz.r_slope = 1.0/(trz.c - trz.d);
         	 break;
	 
      case left_trapezoid:
         	 trz.r_slope = 1.0/(trz.a - trz.b);
         	 trz.l_slope = 0.0;
         	 break;
	 
      case right_trapezoid:
         	 trz.l_slope = 1.0/(trz.b - trz.a);
         	 trz.r_slope = 0.0;
         	 break;
   }  /* end switch  */
   
   return trz;
}  /* end function */

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
float trapz (float x, trapezoid trz) {
   switch (trz.tp) {
	   
      case left_trapezoid:
         	 if (x <= trz.a)
         	    return 1.0;
         	 if (x >= trz.b)
         	    return 0.0;
         	 /* a < x < b */
         	 return trz.r_slope * (x - trz.b);
	 
	 
      case right_trapezoid:
         	 if (x <= trz.a)
         	    return 0.0;
         	 if (x >= trz.b)
         	    return 1.0;
         	 /* a < x < b */
         	 return trz.l_slope * (x - trz.a);
	 
      case regular_trapezoid:
         	 if ((x <= trz.a) || (x >= trz.d))
         	    return 0.0;
         	 if ((x >= trz.b) && (x <= trz.c))
         	    return 1.0;
         	 if ((x >= trz.a) && (x <= trz.b))
         	    return trz.l_slope * (x - trz.a);
         	 if ((x >= trz.c) && (x <= trz.d))
         	    return  trz.r_slope * (x - trz.d);
         	    
	 }  /* End switch  */
	 
   return 0.0;  /* should not get to this point */
}  /* End function */

//////////////////////////////////////////////////////////////////////////////
float min_of(float values[],int no_of_inps) {
   int i;
   float val;
   val = values [0];
   for (i = 1;i < no_of_inps;i++) {
       if (values[i] < val)
	  val = values [i];
   }
   return val;
}



//////////////////////////////////////////////////////////////////////////////
float fuzzy_system (float inputs[],fuzzy_system_rec fz) {
   int i,j;
   short variable_index,fuzzy_set;
   float sum1 = 0.0,sum2 = 0.0,weight;
   float m_values[MAX_NO_OF_INPUTS];
	
   
   for (i = 0;i < fz.no_of_rules;i++) {
      for (j = 0;j < fz.no_of_inputs;j++) {
	   variable_index = fz.rules[i].inp_index[j];
	   fuzzy_set = fz.rules[i].inp_fuzzy_set[j];
	   m_values[j] = trapz(inputs[variable_index],
	       fz.inp_mem_fns[variable_index][fuzzy_set]);
	   } /* end j  */
      
       weight = min_of (m_values,fz.no_of_inputs);
				
       sum1 += weight * fz.output_values[fz.rules[i].out_fuzzy_set];
       sum2 += weight;
   } /* end i  */
 
	
	if (fabs(sum2) < TOO_SMALL) {
      cout << "\r\nFLPRCS Error: Sum2 in fuzzy_system is 0.  Press key: " << endl;
      //~ getch();
      //~ exit(1);
      return 0.0;
   }
   
   return (sum1/sum2);
}  /* end fuzzy_system  */

//////////////////////////////////////////////////////////////////////////////
void free_fuzzy_rules (fuzzy_system_rec *fz) {
   if (fz->allocated){
	   free (fz->rules);
	}
	
   fz->allocated = false;
   return;
}

