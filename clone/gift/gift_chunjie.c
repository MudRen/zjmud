
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
	set_name("�������", ({"chunjie gift"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "���������ָ��mudף����´����֣�\n");
		set("unit", "��");
		set("base_unit", "��");
		set("base_weight", 10);
		set("base_value", 100);
		set("no_put", 1);
		set("no_get", 1);
		set("no_give", 1);
		set("no_drop", 1);
		set("no_steal", 1);
		set("no_beg", 1);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	int num1,num2,num3,num4;

	if (me->is_busy())
		return notify_fail("����æ���ء�\n");

	if (me->is_fighting())
		return notify_fail("����ս���У�����ʹ��"+ name() +"��\n");

	if (me->query("chunjie_gift_times")>7)
		return notify_fail("���Ѿ�������ʹ�ô�������ˡ�\n");

	num1=5000+random(5000);
	me->add("combat_exp",num1);
	num2=5000+random(5000);
	me->add("potential",num2);
	num3=5000+random(5000);
	me->add("experience",num3);
	me->add("chunjie_gift_times",1);
	message_vision("$N������һ" + query("unit") + name() + "��\n", me);
	write(YEL"��ϲ���������"+num1+"�㾭�顣"NOR"\n");
	write(YEL"��ϲ���������"+num2+"��Ǳ�ܡ�"NOR"\n");
	write(YEL"��ϲ���������"+num3+"��ʵս��ᡣ"NOR"\n");
	log_file("gift2", sprintf("%s:%s(%s)ʹ���˴��������\n",ctime(time()),me->query("name"),me->query("id")));
	add_amount(-1);
	me->save();
	return 1;

}
