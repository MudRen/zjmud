
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
	set_name(HIC "������" NOR, ({ "wolong ling" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "����һö���ӵ����ƣ��������һ����ͼ�����Ǳ������������һ��ׯ԰����֪��ʲô���⡣\n");
		set("base_unit", "��");
		set("where", "/d/beijing/road1");
		set("fuben_type", "wolong");
		set("only_do_effect", 1);
		set("yuanbao",100);
		set("base_weight", 1);
	}
	setup();
}


int do_effect(object me)
{
	string family,*skills;
	int i;

	message_vision(CYN "$N" CYN "����һ��" + name() + CYN "����ʼ�۲����ܡ�"NOR"\n", me);
	if(base_name(environment(me))!=query("where"))
	{
		tell_object(me,"����������ϸ������һ�󣬽��ȴ�����ջ�\n");
		return 1;
	}

	if(FUBEN_D->create_fuben(me,query("fuben_type")))
	{
		message_vision(CYN "$N" CYN "������һ�����صĶ��ڣ���֪ͨ�����"NOR"\n", me);
		this_object()->add_amount(-1);
	}

	return 1;
}
