//cwbdao.c
#include <weapon.h>

inherit BLADE;

void create()
{
	set_name("��������", ({ "chuangwang baodao", "blade","baodao" }) );
	set_weight(6000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
	      set("icon", "05071");
		set("value", 500000);
		set("no_drop", 1);
		set("material", "iron");
		set("long", "���Ǵ�����ʹ�ù��ĵ���������м���С�֡�\n" );
		set("wield_msg","һ���׹⣬$n����$N���У�ֻ��������䣬����͸�ǣ�����������Ĵ����ս��\n");
		set("unwield_msg", "$N��$n������䣬�����������ؼ�ֻ��������\n");
	}
	init_blade(150);
	setup();
}
