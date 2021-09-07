// sunfenger.c

inherit COMBINED_ITEM;

void create()
{
	set_name("˳���", ({ "shunfeng er" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "Щ");
		set("long", "���������ħ�����ߣ����Դ�̽(locate)�˵����١�\n");
		set("no_sell", "����ʲô������\n");
		set("base_value", 1);
		set("base_weight", 10);
		set("base_unit", "ֻ");
	}
	set_amount(1);
	setup();
}

void init()
{
	add_action("do_locate", "locate");
}

int do_locate(string arg)
{
	object who;
	object env;

	if (! query_amount())
		return 0;

	if (! arg)
		return notify_fail("�����̽˭�����٣�\n");

	who = find_living(arg);
	if (! objectp(who))
		return notify_fail("û������˵���Ϣ����\n");

	if (! objectp(env = environment(who)))
		return notify_fail("����˲�֪��������Ү��\n");

	write(sprintf("%s��˵����%s...\n", who->name(1), env->short()));
	add_amount(-1);
	return 1;
}


string query_autoload() { return query_amount() + ""; }

void autoload(string param)
{
	int amt;

	if (sscanf(param, "%d", amt) == 1)
		set_amount(amt);
}
