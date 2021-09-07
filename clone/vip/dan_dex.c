
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
	set_name(HIR "����ɵ�" NOR, ({ "huohong xiandan", "dan", "xiandan" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ��ԲԲ�Ļ���ɵ�����˵������������������\n");
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

	if (me->query("gift/unknowdan") >= 5)
	{
		message_vision("$Nҡҡ�λεģ�ͻȻ��žડ�һ����ˤ�˸���ͷ��\n", me);
		tell_object(me, "����ó����Ժ�ͷ�ؽ���ġ�\n");
	} else
	if (random(10) >3 && !me->query("special_skill/lucky"))
	{
		tell_object(me, "��������ú���ûʲô���á�\n");
	      //me->add("gift/unknowdan_fail", 1);
	} else
	{
		tell_object(me, HIM "��ʱ��������ȹ����ѣ�һʱ��ʹ���̣����˹�ȥ��"NOR"\n");
		me->add("dex", 1);
	      me->add("gift/unknowdan", 1);
		write("\n "+HIR+"��ϲ�㣺"+NOR+HIG+"���û���ɵ��ɹ������������������ˣ�����"NOR"\n");
		me->unconcious();
	}

	add_amount(-1);
      return 1;
}


