// wolfarrow.c
 
#include <weapon.h>
 
inherit THROWING;

int is_arrow() { return 1; }
 
void create()
{
	set_name("������", ({ "arrow", "jian" }));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "һ��ϸ���ļ�����ʧ���䣬��ͬ����һ����ɭɭ�ġ�\n");
		set("unit", "��");
		set("base_unit", "��");
		set("base_weight", 150);
		set("base_value", 500);
		set("wound_percent", 90);
	}

	set_amount(1);
	init_throwing(300);
	setup();

	set("no_wield", "�ⲻ������װ���ġ�\n");
}
