// feihuangshi.c
 
#include <weapon.h>
#include <ansi.h>
 
inherit THROWING;
 
void create()
{
	set_name("�ɻ�ʯ", ({ "feihuang shi", "shi" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "��ϸ��ѡ�Ķ���ʯ����Сһ�£�������������Բ��\n");
		set("unit", "��");
		set("value", 0);
		set("base_unit", "��");
		set("base_weight", 1);
		set("base_value", 0);
		set("damage", 5);	//Here the damage=int_throwing, added by King
		set("material", "stone");
		set("wield_msg", HIC"$NѸ�ٵشӰ��������ͳ�һЩ�ɻ�ʯ���������оʹ�������"NOR"\n");
		set("unwield_msg",HIC"$N������ʣ�µķɻ�ʯ�����Żذ������С�"NOR"\n");
	}
	set_amount(20);
	init_throwing(25);
	setup();
}
