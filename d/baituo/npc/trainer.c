//trainer.c

inherit NPC;

void greeting(object);
void init();
void create()
{
	set_name("����", ({ "trainer"}) );
	set("gender", "����" );
	set("age", 25);
	set("long", "���Ǹ��Ͱ����׵Ľ�����\n");
	set("attitude", "friendly");
	set("shen_type", -1);

	set("str", 23);
	set("int", 23);
	set("con", 22);
	set("dex", 20);

	set("max_qi", 300);
	set("max_jing", 300);
	set("neili", 200);
	set("max_neili", 200);
	set("combat_exp", 30000);
	set("score", 20000);

	set_skill("force", 60);
	set_skill("dodge", 70);
	set_skill("unarmed", 70);
	set_skill("parry", 60);
	set_skill("staff",60);

	setup();
}

void init()
{
	object ob;

	if( interactive(ob = this_player()) && !is_fighting() ) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}

}
void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;
	if (check_family(ob, "ŷ������"))
	{
		if (ob->query("qi") < 60)
			message_vision("��������$NЦ���������۰ɣ�û��ϵ���ྡ�����\n",ob);
		else
			message_vision("��������$N������������������Ͱ���\n",ob);
	}
}

void attempt_apprentice(object ob)
{
	if (ob->query("born_family") != "ŷ������")
	{
		command("shake");
		command("say �������ļһ��Ȼ��������ɽ���ң�");
		return;
	}

	command("say �Ǻǣ��Ҳ���ͽ��ȥ��ŷ��ׯ���ɡ�\n");
	return;
}

int accept_fight(object ob)
{
	if (ob->query("born_family") != "ŷ������")
	{
		command("shake");
		command("say �������ļһ��Ȼ��������ɽ���ң�");
		return 0;
	}

	command("say ��Ҫ���ұȻ�������Ժ������ľ����������");
	return 1;
}
