//yuanwai.c

inherit NPC;

void create()
{
	set_name("��Ա��", ({"xiao yuanwai", "xiao","yuanwai" }));
	set("gender", "����");
	set("rank_info/respect", "��Ա��");
	set("age", 50);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("per", 40);
	set("int", 40);
	set("max_kee", 800);
	set("max_gin", 800);
	set("max_sen", 800);
	set("force", 900);
	set("max_force", 900);
	set("force_factor", 60);
	set("max_mana", 900);
	set("mana", 900);
	set("mana_factor", 40);
	set("combat_exp", 300000);
	set_skill("unarmed", 50);
	set_skill("dodge", 50);
	set_skill("parry", 50);
	set_skill("force", 50);
	  
	setup();
	carry_object(__DIR__"obj/choupao")->wear();
}
void check_daughter(object me);

void init()
{
	::init();
	check_daughter(this_object());
}

int accept_object (object who, object ob)
{
	object me = this_object();
	object room = environment(me);
	if (room->query("short") != "���Ҵ���")
		return 0;

	if (ob->query("id") == "jia shu")
	{
		remove_call_out("read_letter");
		call_out("read_letter", 3, me, who, ob);
		return 1;
	}
	return 0;
}

void read_letter(object me, object who, object ob)
{
	destruct (ob);
	reset_eval_cost();

	message_vision("$N�����ţ����ɵ�������¡�\n"
		       "$N������Щ���Ҳ���Ѱ�鳤���ǣ�Ҳû��"
		       "�����Ǻ�����\nԭ�������˹���������¥֮�С�\n\n",
		       me);

	message_vision("$N��$n����������λ" +
		       RANK_D->query_respect(who)+
		       "ǰ����棬�ҿ��ܽ����ͼ������ҵ�Ů���ˣ�\n" +
		       RANK_D->query_respect(who) +
		       "��ݶ��½��Ϸ���α��𰡣�\n", me, who);

	remove_call_out("send_to_fight");
	call_out("send_to_fight", 3, me, who);
}

void send_to_fight (object me, object who)
{
	object yupei = new(__DIR__"obj/yupei");
	yupei->move(who);
	message_vision("$N��$n˵����������λ" +
		       RANK_D->query_respect(who) +
		       "�ٰ��æ������Ů����ȳ�����\n\n",
		       me, who);

	message_vision("$N���´���ȡ��һ�����彻��$n����"
		       "�������ҼҴ����壬����������ϵõģ�\n",
		       me, who);
	message_vision("$N��$nһ�����塣\n", me, who);
	who->save();
}

void check_daughter(object me)
{
  	object room = environment(me);
  	object xiangxiang = present("xiangxiang", room);
  	object who;
  	object yupei;
  	reset_eval_cost();
  	if (room->query("short") != "���Ҵ���")
    		return;

  	if (! xiangxiang || ! xiangxiang->query("leader"))
    		return;
  	if (! (who = present(xiangxiang->query("leader"), room)))
    		return;
  	if (! (yupei = present("yu pei", who)))
    		return;
  	xiangxiang->set_leader(0);
  	xiangxiang->set_temp("no_return", 0);
  	remove_call_out ("cry_daughter");
  	call_out("cry_daughter",2,me,xiangxiang,who);
  	remove_call_out ("announce_success");
  	call_out("announce_success",4,me,who);
}

void cry_daughter(object me, object xiangxiang, object who, object yupei)
{
	object book;
	message_vision("$N����$nһ㶣�Ȼ�������ݺ�ؽ�$n����ȥ��\n",
		       me, xiangxiang); 
	destruct(xiangxiang);
      
	yupei = present("yu pei",who);
	yupei->move(me);
	destruct(yupei);
	command("thank " + who->query("id"));
	command("say ��λ" + RANK_D->query_respect(who) +
		"���Ҷ������ӳ�ħ�ƣ��Ϸ�������һ���飬\n��"
		"���ϴ������ģ����͸�" + RANK_D->query_respect(who) +
		"�ɣ�\n");
	carry_object(__DIR__"obj/book");
	command("give book to " + who->query("id"));
}
