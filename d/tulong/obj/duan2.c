#include <weapon.h>
#include <ansi.h>
inherit BLADE;

void create()
{
	set_name(CYN "���˵�������" NOR, ({ "duan dao" , "blade" , "dao"}) );
	set_weight(30000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("icon", "05065");
		set("long", "һ�����˵ĵ���\n");
		set("value", 0);
		set("rigidity",8000);     
		set("material", "steel");
	}
	init_blade(1);
	setup();
}


