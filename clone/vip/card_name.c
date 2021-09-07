
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
	set_name(HIR "������" NOR, ({ "gengming card" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "�����������յĿ�Ƭ��\n");
		set("unit", "��");
		set("base_unit", "��");
		set("base_value", 500);
		set("yuanbao", 800);
            set("no_sell", 1);
		set("only_do_effect", 1);
		set("base_weight", 10);
	}
	setup();
}

void init()
{
	add_action("change_name","chname");
}

int change_name(string arg)
{
	string result;
	object me=this_player();

	if(me->query("combat_exp", 1) < 1000) 
	{
		tell_object(me,"��û��ʵս�������޷�ʹ��" + name() + "��\n");
		return 1;
	}

	if(!arg||arg=="")
	{
		tell_object(me,INPUTTXT("����ĳ�ʲô���֣�","chname $txt#\n"));
		return 1;
	}

	result = NAME_D->change_name(me, arg);

	if (result)
	{
		tell_object(me,result);
		return 1;
	}
	else
		write("�������ճɹ���\n");

	me->set("purename2",arg);
	me->add("namecard_used",1);
	add_amount(-1);

	return 1;
}

int do_effect(object me)
{
	change_name("");
	return 1;
}
