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
		set("base_weight", 1);
		set("wound_percent", 90);
		set("no_put", 1);
		set("no_get", 1);
		set("no_give", 1);
		set("no_sell", 1);
		set("no_steal", 1);
		set("no_beg", 1);
	}

	set_amount(1);
	init_throwing(300);
	setup();

	set("no_wield", "�ⲻ������װ���ġ�\n");
}
