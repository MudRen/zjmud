// udiamond.c �ռ���ʯ

#include <ansi.h>
#include <armor.h>

inherit HEAD;

void create()
{
	set_name(HIW "����֮" BLINK HIW "��ʯ" NOR, ({ "ultra diamond" }) );
	set_weight(25);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", HIW "��������������֮ף����������ʯ��"NOR"\n");
		set("value", 20000);
		set("unit", "��");
		set("can_be_enchased", 1);
		set("magic/type", "lighting");
		set("magic/power", 220);
		set("armor_prop/per", 12);
		set("wear_msg", HIC "$N" HIC "����ذ�$n"
		    HIC "����ͷ�ϡ�"NOR"\n");
		set("remove_msg", HIC "$N" HIC "����ذ�$n"
		    HIC "��ͷ��ժ��������"NOR"\n");
	}
	setup();
}

int query_autoload() { return 1; }
