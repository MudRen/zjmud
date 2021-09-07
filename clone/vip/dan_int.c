
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
	set_name(HIY "�����ɵ�" NOR, ({ "xian dan", "dan", "xiandan" }) );
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "һ��ԲԲ���ɵ�����˵���˿�����ǿ������\n");
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

	if (me->query("gift/xiandan") >= 5)
	{
		message_vision("$N��Ȼ�����ۡ�������һ�ء�\n", me);
		tell_object(me, "���������ǳ��Ŀࡣ\n");
	} else
	if (random(10) >3 && !me->query("special_skill/lucky"))
	{
		tell_object(me, "��������ú���ûʲô���á�\n");
	      //me->add("gift/xiandan_fail", 1);
	} else
	{
		tell_object(me, HIG "һ�ɻ�����Ȼ����������"
			    "��ͷʹ���ѣ�ǡ�ڴ�ʱһ������֮��"
			    "��Ȼ���𣬶ٸ���̩�ޱȡ�\n");
		me->add("int", 1);
	      me->add("gift/xiandan", 1);
	     write("\n "+HIR+"��ϲ�㣺"+NOR+HIG+"�����ɵ��ɹ������������ԡ������ˣ�����"NOR"\n");
	}

	add_amount(-1);
      return 1;
}

