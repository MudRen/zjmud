//keeper.c

inherit NPC;

void create()
{
	set_name("��ף", ({ "keeper" }) );
	set("gender", "����" );
	set("age", 60);
	set("long", "������˿�������ʮ�����ˣ�����ȴ�ܺá�\n");
	set("combat_exp", 100);
	set("attitude", "friendly");

	setup();
}

void init()
{
	object ob;
	::init();
	if (interactive(ob = this_player()) && !is_fighting()) 
	{
		call_out("greeting", 1, ob);
	}
}

void greeting(object ob)
{
	if (! ob || ! present(ob, environment(this_object()))) 
		return;

	say("��ף˵������λ" + RANK_D->query_respect(ob) +
	    "��������Ǯ�ɡ�\n");
}

