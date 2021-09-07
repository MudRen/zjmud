// meigui.c

#include <ansi.h>
#include <armor.h>

inherit HEAD;

void create()
{
	set_name(HIR "õ��" NOR, ({ "rose", "meigui" }));
	set_weight(10);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("no_sell", 1);
		set("long", HIR "һ���ɫ��õ�壬������͸��һ����Ȼ��"NOR"\n");
		set("value", 100000);
		set("material", "plant");
		set("armor_prop/armor", 0);
		set("armor_prop/personality", 3);
		set("wear_msg", HIC "$N" HIC "����ذ�һ��$n"
				HIC "����ͷ�ϣ���ȻһЦ��\n");
		set("remove_msg", HIC "$N" HIC "���ĵ�̾��"
				  "��������$n" HIC "��ͷ��ժ��������\n");
	}
	setup();
}

