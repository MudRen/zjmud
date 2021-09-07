// xue-dao.c

#include <ansi.h>
#include <weapon.h>

inherit BLADE;

void create()
{
	set_name(HIR "Ѫ��" NOR, ({ "blood blade", "blade" }));
	set_weight(1000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", HIR "����һ�ѿɲ�����������͵���"
			    "����������ŵ�����ѪӰ��һƬ���졣"NOR"\n" );
		set("value", 200000);
	    // set("icon", "05038");
		set("material", "steel");
		set("no_sell", "���... ����е�Ź�...");
		set("wield_msg", "$N��ৡ���һ�����һ��$n�������С�\n");
		set("unwield_msg", "$N�����е�$n��ص��ʡ�\n");
	}
	init_blade(120);
	setup();
}
