// tielianzi.c
 
#include <weapon.h>
#include <ansi.h>

inherit THROWING;
 
void create()
{
	set_name("������", ({ "tie lianzi", "lianzi", "zi" }));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "�������Ƶ�����״������\n");
		set("unit", "��");
		set("base_unit", "��");
		set("base_weight", 1);
		set("base_value", 1);
		set("material", "iron");
		set("wield_msg", HIC "$NѸ�ٵشӰ��������ͳ�"
				 "һЩ�����ӣ��������оʹ�������"NOR"\n");
		set("unwield_msg", HIC "$N������ʣ�µ������Ӿ����Żذ������С�"NOR"\n");
	}
	set_amount(30);
	init_throwing(15);
	setup();
}
