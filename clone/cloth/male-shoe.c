// man-shoe.c
 
#include <armor.h>
 
inherit BOOTS;
 
void create()
{
	set_name("ţƤѥ", ({ "pi xue", "xue" }) );
	set_weight(800);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("material", "leather");
		set("unit", "˫");
	      set("icon", "05004");
		set("long", "����һ˫���Ϻ�ţƤ����Ƥѥ��\n");
		set("value", 0);
		set("armor_prop/dodge", 8);
	}
	setup();
}
