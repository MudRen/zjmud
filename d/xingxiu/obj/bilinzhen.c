// tielianzi.c
#include <weapon.h>
#include <ansi.h>

inherit THROWING;

void create()
{
	set_name(HIG"������"NOR, ({ "bilin zhen", "zhen" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "Щ");
		set("value", 0);
		set("base_unit", "ö");
		set("base_weight", 300);
		set("base_value", 0);
		set("material", "iron");
		set("long", HIG "��������������ʹ�õģ�����������"
			    "�㶾���볤������������Ĺ⡣"NOR"\n");
		set("wield_msg", HIC "$NѸ�ٵش���������һЩ�����룬��"
				 "�����оʹ�������"NOR"\n");
		set("unwield_msg", HIC "$N������ʣ�µı�����һ���Ͳ�����"
				   "��"NOR"\n");
	}
	set_amount(50);
	init_throwing(50);
	setup();
}
