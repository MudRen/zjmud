#include <weapon.h>
#include <ansi.h>

inherit CLUB;

void create()
{
	set_name(HIY"����"NOR, ({ "flag","qi"}) );
	set_weight(15000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "��������һͷ��ӥ��˫����չ���������䡣\n");
		set("value", 300);
		set("material", "silk");
		set("wield_msg", "$N�ó�һ��$n������ʾ�⡣\n");
		set("unwield_msg", "$N�������е�$n��\n");
	}
	init_club(10);
	setup();
}

