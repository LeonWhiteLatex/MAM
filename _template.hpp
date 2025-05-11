/*******************************************************************************\
*NAME: _TEMPLATE								*
*DESCRIPTION: Template inheritance object for output, currently used for	*
* fragment shader color output							*
*OBJECTS:									*
* ~_template -- inheritable color ouputer, used for inheritance					*
*	METHODS:								*
*	 -colr() -- returns array of 3 colors					*
\*******************************************************************************/

#ifndef _TEMPLATE_HPP__
#define _TEMPLATE_HPP__

class _template{
public:
	virtual float* colr()=0; //replace with texture later
	//virtual void update()=0;
};

#endif
