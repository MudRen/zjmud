// yrose.c

#include <ansi.h>
#include <armor.h>

inherit HEAD;

void create()
{
	set_name(HIY "õ��" NOR, ({ "rose", "meigui" }));
	set_weight(10);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", HIY "һ���ɫ��õ�塣"NOR"\n");
		set("value", 10);
		set("material", "plant");
		set("armor_prop/armor", 0);
		set("armor_prop/personality", 3);
		set("wear_msg", HIC "$N" HIC "����ذ�һ��$n"
				HIC "����ͷ�ϣ��ĵ������óݸ��Ӷ��ˡ�\n");
		set("remove_msg", HIC "$N" HIC "�����̾��"
				  "��������$n" HIC "��ͷ��ժ��������\n");
	}
	setup();
}

