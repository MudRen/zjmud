#include <weapon.h>
#include <ansi.h>

inherit HAMMER;

void create()
{
	set_name(HIG "����" NOR+HIR "����" NOR, ({ "green xigua","xigua","hammer" }) );
	set_weight(160000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "�������ɾ������ɣ���������̺ڼ���֮ɫ������һ�ԣ�ϵ�Ը�����\n");
		set("value", 3000);
		set("material", "iron");
		set("wield_msg", "$N�ó�һ��$n��������������Ȼ���������С�\n");
		set("unwield_msg", "$N�������е�$n��\n");
	}
	init_hammer(80);
	setup();
}

