// tielianzi.c
#include <weapon.h>
#include <ansi.h>

inherit THROWING;

void create()
{
	set_name(HIG"���ĵ�"NOR, ({ "lianxin dan", "dan" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "Щ");
		set("value", 0);
		set("base_unit", "��");
		set("base_weight", 300);
		set("base_value", 0);
		set("material", "iron");
		set("long", HIG"���ĵ��������ɴ㶾�������볤������������Ĺ⡣"NOR"\n");
		set("wield_msg", HIC"$NѸ�ٵش�¹Ƥ��������һЩ���ĵ����������оʹ�������"NOR"\n");
		set("unwield_msg",HIC"$N������ʣ�µ����ĵ��ջ�¹Ƥ���С�"NOR"\n");
	}
	set_amount(50);
	init_throwing(10);
	setup();
}
