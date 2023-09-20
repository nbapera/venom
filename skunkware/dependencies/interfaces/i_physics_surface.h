#pragma once

struct surfacephysicsparams_t
{
	float    friction;
	float    elasticity; // collision elasticity - used to compute coefficient of restitution
	float    density;    // physical density (in kg / m^3)
	float    thickness;    // material thickness if not solid (sheet materials) in inches
	float    dampening;
};

struct surfaceaudioparams_t
{
	float    reflectivity;            // like elasticity, but how much sound should be reflected by this surface
	float    hardnessFactor;            // like elasticity, but only affects impact sound choices
	float    roughnessFactor;        // like friction, but only affects scrape sound choices   
	float    roughThreshold;            // surface roughness > this causes "rough" scrapes, < this causes "smooth" scrapes
	float    hardThreshold;            // surface hardness > this causes "hard" impacts, < this causes "soft" impacts
	float    hardVelocityThreshold;    // collision velocity > this causes "hard" impacts, < this causes "soft" impacts   
};

struct surfacesoundnames_t
{
	unsigned short    stepleft;
	unsigned short    stepright;
	unsigned short    impactSoft;
	unsigned short    impactHard;
	unsigned short    scrapeSmooth;
	unsigned short    scrapeRough;
	unsigned short    bulletImpact;
	unsigned short    rolling;
	unsigned short    breakSound;
	unsigned short    strainSound;
};


struct surfacegameprops_t
{
public:
	float			  maxSpeedFactor; //0x0000
	float			  jumpFactor; //0x0004
	char			  pad00[0x4]; //0x0008
	float			  flPenetrationModifier; //0x000C
	float			  flDamageModifier; //0x0010
	unsigned short    material; //0x0014
	char			  pad01[0x3];

};//Size=0x0019

struct surfacedata_t
{
	surfacephysicsparams_t     physics;
	surfaceaudioparams_t	   audio;
	surfacesoundnames_t        sounds;
	surfacegameprops_t         game;
};

class i_physics_surface
{
public:
	surfacedata_t* get_surface_data(int surface_data_index)
	{
		using original_fn = surfacedata_t*(__thiscall*)(i_physics_surface*, std::uint32_t);
		return (*(original_fn**)this)[5](this, surface_data_index);
	}
};