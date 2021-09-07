// waiter.c

inherit NPC;
#include <ansi.h>;

void create()
{
	set_name("ά�����Ů", ({ "girl", "shaonv", "shao nv" }) );
	set("gender", "Ů��" );
	set("age", 19);
	set("long",
		"��λС����һ��æ��æ�⣬���Ϳ�����˵��Ц��\n");
	set("combat_exp", 100);
	set("attitude", "friendly");
	set("rank_info/respect", "С����");
	setup();
}

void init()
{	
	object ob;

	::init();
	if( interactive(ob = this_player()) && !is_fighting() ) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}

void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;
	switch( random(2) ) {
	case 0:
		say( "ά�����ŮЦ�����˵������λ" + RANK_D->query_respect(ob)
			+ "�������ȱ��̲裬ЪЪ�Ȱɡ�\n");
		break;
	case 1:
		say( "ά�����Ů�����֣���æ˵������λ" + RANK_D->query_respect(ob)
			+ "�����������\n");
		break;
	}
}

int accept_object(object who, object ob)
{
	
	if (ob->query("money_id") && ob->value() >= 500) 
	{
		tell_object(who, "ά�����Ůæ˵������л����������¥ЪϢ�ɡ�\n");

		who->set_temp("rent_paid",1);

		return 1;
	}

	return 0;
}
