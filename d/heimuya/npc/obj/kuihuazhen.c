// kuihuazhen.c

#include <weapon.h>

inherit THROWING;

void create()
{
	set_name("������", ({ "kuihuazhen" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long",     "��������һ��ר�Ŵ��Ƶİ��������μ�����\n");
		set("unit", "��");
		set("base_unit", "��");
		set("base_weight", 1);
		set("base_value", 0);
		set("value", 0);
	}
	set_amount(200);
	init_throwing(10);
	setup();
}

