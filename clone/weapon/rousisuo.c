#include <ansi.h>

#include <weapon.h>

inherit WHIP;

void create()
{
	set_name(WHT "��˿��" NOR,({ "rousi suo", "suo", "rousi" }) );
	set_weight(1000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("value", 200000);
		set("no_sell", 1);
		set("long", HIW "һ��ǳ������ϸ˿�������˿��֯������������֮һ��"NOR"\n" );
		set("wield_msg", HIW "$N" HIW "�ó�һ��$n" HIW "������̯�����������С�"NOR"\n" );
		set("unwield_msg", HIW "$N" HIW "��$n" HIW "�ջسɾ��Ż����䡣"NOR"\n" );
		set("material", "white silk");
		set("stable", 0);
	}
	init_whip(35);
	setup();
}
