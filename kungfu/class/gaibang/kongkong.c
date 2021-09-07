// kongkong.c

inherit NPC;
inherit F_MASTER;
inherit F_UNIQUE;

void consider();

void create()
{
	seteuid(getuid());
	set_name("�տն�", ({ "kong kong","beggar","qi gai","kong" }) );
	set("title", "������ؤ");
	set("gender", "����" );
	set("age", 53);
	set("long", "һ��������˪֮ɫ������ؤ��\n");
	set("attitude", "peaceful");

	set("str", 25);
	set("con", 25);
	set("int", 25);
	set("dex", 25);
	set("kar", 100);

	set("qi", 2500);
	set("max_qi", 2500);
	set("jing", 1200);
	set("max_jing", 1200);
	set("neili", 4500);
	set("max_neili", 4500);
	set("jiali", 80);

	set("shen_type", 0);
	set("thief", 0);
	set("combat_exp", 550000);

	set_skill("force", 150);
	set_skill("unarmed", 100);
	set_skill("sword", 80);
	set_skill("dodge", 150);
	set_skill("parry", 150);
	set_skill("stealing", 190);
	set_skill("begging", 150);
	set_skill("checking", 150);
	set_skill("jiaohua-neigong", 150);
	set_skill("changquan", 100);
	set_skill("feiyan-zoubi", 150);

	map_skill("force", "jiaohua-neigong");
	map_skill("unarmed", "changquan");
	map_skill("parry", "changquan");
	map_skill("dodge", "feiyan-zoubi");

	create_family("ؤ��", 19, "�˴�����");

	set("chat_chance", 2);
	set("chat_msg", ({
		"�տն�˵��: ���ĵĴ�ү�ġ� ����Ҫ���ļ���ͭ��ɡ�\n",
		"�տն�������ش��˸���Ƿ��\n",
		"�տն�����׽ס�����ϵ�ʭ�ӣ����: ��������û�����⣬ȫ�����Ǹ�ҧ���ˡ� \n",
		"�տն�˵��: ���ĵĴ�ү�ġ� ����Ҫ���ļ���ͭ��ɡ�\n",
		"�տն�������ش��˸���Ƿ��\n",
		"�տն�����׽ס�����ϵ�ʭ�ӣ����: ��������û�����⣬ȫ�����Ǹ�ҧ���ˡ� \n",
		(: random_move :)
	}) );

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: exert_function, "recover" :),
	}) );

	setup();

	carry_object("/clone/food/jitui");
	carry_object("/clone/food/jiudai");
	add_money("silver", 10);
}

void attempt_apprentice(object ob)
{
	if( ob->query("detach/ؤ��") )
	{
		command("say ��������Ի�ͷ�ݣ�û�ţ�");
		return 0;
	}

	if( ob->query("betrayer") )
	{
		command("say ����ؤ����Ȼ�ǽл��ӣ���������������·�������չ���ʦ�ģ�");
		return 0;
	}

	if (ob->query("family/family_name") != "ؤ��")
	{
		command("say �٣����Ȼ�Ѿ�������ʦָ�㣬���������Ͻл���ʲô��");
		return 0;
	}

	command("say �ðɣ�ϣ��" + RANK_D->query_respect(ob) +
	"�ܺú�ѧϰ�����书�������ڽ����д���һ����Ϊ��");
	command("recruit " + ob->query("id"));
	if((string)ob->query("class") != "beggar")
		ob->set("class", "beggar");
}

int recognize_apprentice(object ob, string skill)
{
	if (ob->query("family/family_name") != "ؤ��")
		return 0;

	if (skill != "stealing" && skill != "begging" &&
	    skill != "checking")
	{
		message_vision("$n����ǰȥ������$N���ҿ���������û������$n��˵ʲô��\n",
			       this_object(), ob);
		return -1;
	}

	return 1;
}

void init()
{	
	object ob;

	::init();
	if( interactive(ob = this_player()) ) {
		remove_call_out("stealing");
		call_out("stealing", 1, ob);
	}
}

void stealing(object ob)
{
	mapping fam; 
 
	if (! ob || environment(ob) != environment() ||
	    ((fam = ob->query("family")) && fam["family_name"] == "ؤ��") ||
	    (int)ob->query_skill("taoism", 1) > 30 ||
	    ob->query_int() > 30)
		return;

	switch(random(5))
	{
		case 0:
		       command("hehe " + ob->query("id"));
		       command("beg coin from " + ob->query("id"));
		       command("buy jitui");
		       break;
		case 1:
		       command("grin " + ob->query("id"));
		       command("steal silver from " + ob->query("id"));			
		       command("eat jitui");
		       break;
		case 2:
		       command("hi " + ob->query("id"));
		       command("steal gold from " + ob->query("id"));			
		       command("drink jiudai");
		       break;
		case 3:
		       command("pat " + ob->query("id"));
		       command("beg jiudai from " + ob->query("id"));	
		       command("eat jitui");
		       break;
		case 4:
		       command("walkby " + ob->query("id"));
		       command("beg jitui from " + ob->query("id"));	
		       command("drink jiudai");
		       break;
	}
}


int accept_object(object me, object obj)
{
	if (obj->query("money_id") && obj->value() >= 1)
	{
		command("smile");
		command("say ��л�� ! ��ʵ�һ����е�Ǯ�ģ����"
			"ֻ������������� !");
		return 1;
	} else
	{
		command("shake");
		command("say ���ֶ������Ҫ ! ��һ��ȥ !");
		command("give " + obj->query("id") + " to " +
		me->query("id"));
	}

	return 1;
}

int accept_fight(object me)
{
	command("say " + RANK_D->query_respect(me) + "������С������뿪��\n");
	return 0;
}

void die()
{
	object ob;
	message_vision("$N���ڵ��ϣ����������£����ˡ�\n", this_object());
	destruct(this_object());
}

