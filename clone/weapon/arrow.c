// arrow.c
 
#include <weapon.h>
 
inherit THROWING;

int is_arrow() { return 1; }
 
void create()
{
	set_name("���", ({ "arrow", "jian" }));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "һ��ϸ���ļ��������޳�����ʧ������\n");
		set("unit", "��");
		set("base_unit", "��");
		set("base_weight", 100);
		set("base_value", 200);
		set("wound_percent", 80);
	}

	set_amount(1);
	init_throwing(200);
	setup();

	set("no_wield", "�ⲻ������װ���ġ�\n");
}
