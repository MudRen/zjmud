
#include <ansi.h>

inherit COMBINED_ITEM;

string query_autoload() { return query_amount() + ""; }

void autoload(string param)
{
	int amt;

	if (sscanf(param, "%d", amt) == 1)
		set_amount(amt);
}

void setup()
{
	set_amount(1);
	::setup();
}

void create()
{
	set_name(HIG "������" NOR, ({ "shenli wan", "wan"}) );
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ��ԲԲ�������裬��˵���˿�����ǿ������\n");
		set("unit", "��");
		set("base_unit", "��");
		set("base_weight", 10);
		set("base_value", 10000);
		set("yuanbao", 100);
            set("no_sell", 1);
		set("suit_point", 300);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	message_vision("$Nһ������������һ" + query("unit") + name() + "��\n", me);

	if (me->query("gift/shenliwan") >= 5)
	{
		message_vision("$Nգգ�ۡ�\n", me);
		tell_object(me, "�������ҩûɶζ���������绨���óԡ�\n");
	} else
	if (random(10) >3 && !me->query("special_skill/lucky"))
	{
		tell_object(me, "��������ú���ûʲô���á�\n");
	} else
	{
		tell_object(me, HIR "�����˫�ۼ������ѣ�������������"NOR"\n");
		me->add("str", 1);
	      me->add("gift/shenliwan", 1);
		write("\n "+HIR+"��ϲ�㣺"+HIG+"����������ɹ�������������������ˣ�����"NOR"\n");
	}

	add_amount(-1);
      return 1;
}



