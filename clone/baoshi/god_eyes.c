// god_eyes.c �ϵ�֮��

#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
	set_name(HIG "�ϵ�֮" + HIM + "��" NOR, ({ "god eyes","eyes" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", HIC"һ����˸��"HIY"��Ŀ��â"HIC"��"HIG"��ʯ"HIC"����˵���ﲢ�������˼䣬���˾�η֮����Ȼ������"NOR"\n");
		set("base_value", 2000000);
		set("base_weight", 1);
		set("base_unit", "��");
		set("can_be_enchased", 1);
		set("magic/type", "all");
		set("magic/power", 200);
	}
	set_amount(1);
	setup();
}
