// sample master.c code

inherit NPC;
inherit F_MASTER;

void consider();
string ask_me();
int accept_object(object ob, object obj);

void create()
{
	set_name("����", ({"jian zhanglao", "jian", "zhanglao"}));
	set("title", "ؤ��Ŵ�����");
	set("nickname", "ִ������");
	set("gender", "����");
	set("no_get", 1);
	set("age", 50);
	set("long", 
		"������ؤ���ִ�����ϣ�������ִ�Ʒ����Լ�������ȡ�"
		"������������𣬵�������˭���������־������顣\n");

	set("attitude", "peaceful");
	
	set("str", 27);
	set("int", 22);
	set("con", 24);
	set("dex", 20);

	set("qi", 900);
	set("max_qi", 900);
	set("jing", 100);
	set("max_jing", 100);
	set("neili", 1500);
	set("max_neili", 1500);
	set("jiali", 100);

	set("combat_exp", 880000);
	set("score", 20000);

	set_skill("force", 170);
	set_skill("jiaohua-neigong", 170);
	set_skill("unarmed", 165);
	set_skill("changquan", 165);
	set_skill("dodge", 150);
	set_skill("feiyan-zoubi", 150);
	set_skill("parry", 175);
	set_skill("staff", 150);
	set_skill("jiaohua-bangfa", 150);

	map_skill("force", "jiaohua-neigong");
	map_skill("unarmed", "changquan");
	map_skill("parry", "changquan");
	map_skill("dodge", "feiyan-zoubi");
	map_skill("staff", "jiaohua-bangfa");

	create_family("ؤ��", 18, "�Ŵ�����");

	set("inquiry", ([
		"������" :     (: ask_me :)
	]));

	set("chat_chance_combat", 20);
	set("chat_msg_combat", ({
		(: exert_function, "recover" :),
	}) );

	setup();

	carry_object("/clone/weapon/tiegun")->wield();
}

void init()
{
	object ob;
	mapping myfam;
	
	::init();
	if (interactive(ob = this_player()) && ! is_fighting())
	{
		myfam = (mapping)ob->query("family");
		if ((! myfam || myfam["family_name"] != "ؤ��") &&
		    ! wizardp(ob))
		{
			remove_call_out("saying");
			call_out("saying", 1, ob);
		}
	}
}

void saying(object ob)
{
	if (! ob || environment(ob) != environment())
		return;

	message_vision("\n���Ͽ���$Nһ�ۣ������˵����������������˼�˵�Ҳ���"
	    "�������ؤ����ӣ�\n���ֲ�����ؤ��Ҵ����ܿ��԰ɣ���\n"
	    "˵������һ̧��$N˳��Ӧ��һ������ɵġ�ƨ�����ƽɳ����ʽ��"
	    "������ߴ\n\n", ob);
	remove_call_out("kicking");
	call_out("kicking", 1, ob);
	
}

void kicking(object ob)
{
	if (! ob || environment(ob) != environment())
		return;

	ob->move("/d/city/pomiao");
	message("vision","ֻ�����ء���һ����������" +  ob->query("name") +
		"��С������˳�����ƨ������һ�������Ьӡ��\n",
		environment(ob), ob);
}

void attempt_apprentice(object ob)
{
	command("say �Ϸ���ͽ�ܣ�" + RANK_D->query_respect(ob) + "������ذɡ�");
}

string ask_me()
{
	mapping fam;
	object ob, me;
	string *sname;
	int i;

	me = this_player();

	if (is_busy() || is_fighting())
		return "���һ���������æ�ء�\n";

	if (! (fam = me->query("family")) || fam["family_name"] != "ؤ��")
		return RANK_D->query_respect(me) +
		"�뱾��������������֪�˻��Ӻ�̸��";

	if (me->query("combat_exp", 1) < 1000)
		return "�ߣ������㱾��Ҳ����˼��Ҫ�����";

	if (present("qingzhu ling", me))
		return "�����ϲ����Ѿ�������������";

	ob = new(__DIR__"obj/qingzhu-ling");
	ob->move(me);
	message_vision("$N���һ�������\n",me);

	start_busy(3 + random(5));
	return "�ðɣ�ƾ���������������������ͬ�Ŵ�ʦ����ս��";
}

int accept_object(object ob, object obj)
{
	object me = this_object();

	if (ob->query_temp("have_cloth") && obj->query("id") == "po bu")
	{
		command("say ��Ȼ�������͵��μǰ�棬Ϊ�������");
		message_vision("$N�ӹ����Ʋ���Ȼ���������$n�����·��ϣ�"
			       "ٲȻһ���¿ڴ���\n", me, ob);
		ob->delete_temp("have_cloth");
		ob->set("title", ob->query_temp("newtitle"));
		ob->delete_temp("newtitle");
		if (ob->query("title") == "ؤ��һ������")
		{
			ob->add("combat_exp", 250);
			ob->add("potential", 250);
			ob->set("beggarlvl", 1);
		}
		if (ob->query("title") == "ؤ���������")
		{
			ob->add("combat_exp", 500);
			ob->add("potential", 500);
			ob->set("beggarlvl", 2);
		}
		if (ob->query("title") == "ؤ����������")
		{
			ob->add("combat_exp", 1000);
			ob->add("potential", 1000);
			ob->set("beggarlvl", 3);
		}
		if (ob->query("title") == "ؤ���Ĵ�����")
		{
			ob->add("combat_exp", 1500);
			ob->add("potential", 1500);
			ob->set("beggarlvl", 4);
		}
		if (ob->query("title") == "ؤ���������")
		{
			ob->add("combat_exp", 2000);
			ob->add("potential", 2000);
			ob->set("beggarlvl", 5);
		}
		if (ob->query("title") == "ؤ����������")
		{
			ob->add("combat_exp", 3000);
			ob->add("potential", 3000);
			ob->set("beggarlvl", 6);
		}
		if (ob->query("title") == "ؤ���ߴ�����")
		{
			ob->add("combat_exp", 4000);
			ob->add("potential", 4000);
			ob->set("beggarlvl", 7);
		}
		if (ob->query("title") == "ؤ��˴�����")
		{
			ob->add("combat_exp", 5000);
			ob->add("potential", 5000);
			ob->set("beggarlvl", 8);
		}
		if (ob->query("title") == "ؤ��Ŵ�����")
		{
			ob->add("combat_exp", 10000);
			ob->add("potential", 10000);
			ob->set("beggarlvl", 9);
		}
		destruct(obj);
		return 1;
	}
}
