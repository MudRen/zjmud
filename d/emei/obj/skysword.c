//ytjian.c ���콣
#include <ansi.h>
#include <weapon.h>

inherit SWORD;

void create()
{
	set_name(CYN "���콣" NOR,({"sky sword","sword","jian"}));
	set_weight(5000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "�˽��˹������ط򸾴��죬�����������\n");
		set("material", "steel");
		set("no_sell", 1);
		set("icon","05060");
		set("value", 1000000);
		set("wield_msg", CYN "���콣�����߰�Ծ�����ʣ�����$N���У������
�貵ĺ��⣬���Ϊ֮��ɫ��"NOR"\n");
		set("unwield_msg", CYN "$N���н��⽥����������Ļ����������â��"NOR"\n");
       }
       init_sword(220);
       setup();
}
