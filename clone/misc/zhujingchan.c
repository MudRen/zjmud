inherit ITEM;
#include <ansi.h>

void create()
{
	set_name(HIR"�쾦"HIW"��"HIR"�"NOR, ({"chan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "ֻ");
		set("value", 40000);
		set("long", "����һǧ���ѵ�һ�����쾦��󸣬ͨ��͸����Ω�۳ʳ�"
			    "ɫ���ܽ�ٶ���\n");
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	message_vision(HIR "$N" HIG "����һֻ�쾦��󸣬ֻ��һ�ɵ���һƬ���ȣ�"
		       "��Ϣ��ת�ޱ�˳����"NOR"\n", me);
	set_temp("nopoison", 3);
	destruct(this_object());
	return 1;
}

