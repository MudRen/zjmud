// tiedan.c
#include <weapon.h>
#include <ansi.h>

inherit THROWING;

void create()
{
	set_name(HIW"����"NOR, ({ "tiedan", "dan" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "Щ");
		set("value", 0);
		set("base_unit", "ö");
		set("base_weight", 300);
		set("base_value", 0);
		set("material", "iron");
		set("long", HIG"һЩ��Բ����������һ�����͵İ�����"NOR"\n");
		set("wield_msg", HIC"$NѸ�ٵش���������һЩ�������������оʹ�������"NOR"\n");
		set("unwield_msg",HIC"$N������ʣ�µ�����һ���Ͳ����ˡ�"NOR"\n");
	}
	set_amount(50);
	init_throwing(30);
	setup();
}
