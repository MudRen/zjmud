// lengyue.c ���±���
#include <weapon.h>

inherit BLADE;

#include <ansi.h>

void create()
{
	set_name(HIG "���±���" NOR, ({ "moon blade", "blade" }));
	set_weight(7000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("value", 1000000);
	      set("icon", "05072");
		set("no_sell", "��...�����չ����˵�...\n");
		set("material", "steel");
		set("long", "���Ǻ����洫�ı���������ɭɭ�������ޱȡ�\n" );
		set("wield_msg", HIG "$N" HIG "ץ�𵶱�������ֻ����ǰ���һ"
				 "�����������ˣ�$N" HIG "�����Ѿ�����һ��$n"
				 HIG "��������ˮ����ת������"NOR"\n");
		set("unwield_msg", HIW "$N" HIW "������Х�����ип�����$n"
				   HIW "��ص��ʡ�\n");
	}
	init_blade(180);
	setup();
}

