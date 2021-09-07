//xiaoer.c

inherit KNOWER;

void create()
{
	set_name("��С��", ({"xiaoer","xiaoer","xiao","waiter","er"}));
	set("shop_id",({"waiter","xiaoer","xiao","er"}));
	set("shop_title","��С��");
	set("gender", "����");
	set("combat_exp", 2000);
	set("age", 21);
	set("per", 23);
	set("attitude", "friendly");
	set("shen_type", 1);
	set_skill("unarmed", 10);
	setup();
	carry_object(__DIR__"obj/linen")->wear();
	add_money("silver", 1);

}

void greeting(object ob)
{
	if (! ob || ! visible(ob) || environment(ob) != environment())
		return;
	say(name() + "Ц�����˵������λ" + RANK_D->query_respect(ob) +
	    "������ЪЪ�ţ���Ϣһ�°ɡ�\n");
}

int accept_object(object who, object ob)
{
	if (ob->query("money_id") && ob->value() >= 300)
	{
		tell_object(who, "С��һ������˵������л���ϣ��͹�����¥ЪϢ��\n");
		who->set_temp("rent_paid", 1);
		return 1;
	}
	return 0;
}
