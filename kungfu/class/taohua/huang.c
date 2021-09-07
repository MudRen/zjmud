// huang.c

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;
inherit F_QUESTER;

#include <ansi.h>
#include "taohua.h"

void   consider();
string ask_me();
int    ask_leave();
int    ask_medicine();
mixed  ask_qing();
mixed  ask_music_book();

mixed  try_to_learn_bibo();
mixed  try_to_learn_lanhua();
mixed  try_to_learn_tanzhi();
mixed  try_to_learn_yuxiao();

void create()
{
	set_name("��ҩʦ", ({"huang yaoshi", "huang", "yaoshi"}));
	set("title", "�һ�����");
	set("nickname", HIY "��а" NOR );
	set("gender", "����");
	set("age", 42);
	set("long", 
		"�������һ����������ºö�ȫ�ɼ��ģ���˱��˳�������а����\n");
	set("attitude", "peaceful");
	set("class", "scholar");
	
	set("str", 31);
	set("int", 38);
	set("con", 34);
	set("dex", 32);
	set("shen_type", 1);

	set("chat_chance", 1);
	set("chat_msg", ({
		"��ҩʦ̾�˿����������� ���� �ض�������ĺ��ӣ���С��û���� ������\n",
		"��ҩʦ��ͷ��˼����Ȼ���\n",
	}));

	set("qi", 5800);
	set("max_qi", 5800);
	set("jing", 2900);
	set("max_jing", 2900);
	set("neili", 7000);
	set("max_neili", 7000);
	set("jiali", 100);

	set("combat_exp", 2500000);
	 
	set_skill("force", 270);	     // �����ڹ�
	set_skill("bibo-shengong", 270);     // �̲���
	set_skill("luoying-xinfa", 270);     // ��Ӣ�ķ�
	set_skill("hand", 250);	      // �����ַ�
	set_skill("finger", 270);	    // ����ָ��
	set_skill("tanzhi-shentong", 270);   // ��ָ��ͨ
	set_skill("unarmed", 220);	   // ����ȭ��
	set_skill("strike", 220);	    // ����ȭ��
	set_skill("luoying-shenzhang", 250); // ��Ӣ����
	set_skill("xuanfeng-leg", 250);      // ����ɨҶ��
	set_skill("dodge", 270);	     // ��������
	set_skill("anying-fuxiang", 270);    // ��Ӱ����
	set_skill("parry", 270);	     // �����м�
	set_skill("sword", 270);	     // ��������
	set_skill("throwing", 270);	     // ��������
	set_skill("luoying-shenjian", 270);  // ��Ӣ��
	set_skill("yuxiao-jian", 270);       // ���｣��
	set_skill("lanhua-shou", 270);       // ������Ѩ��
	set_skill("qimen-wuxing", 250);      // ��������
	set_skill("count", 300);	     // ��������
	set_skill("mathematics", 300);       // ����
	set_skill("literate", 250);	  // ����ʶ��
	set_skill("chuixiao-jifa", 300);     // ���＼��
	set_skill("bihai-chaosheng", 300);   // �̺�����
	set_skill("taohua-yuan", 250);       // �һ�Թ
	set_skill("medical", 300);	   // ����ҽ��
	set_skill("taohua-yaoli", 300);      // �һ�ҩ��

	map_skill("force"  , "bibo-shengong");
	map_skill("finger" , "tanzhi-shentong");
	map_skill("hand"   , "lanhua-shou");
	map_skill("unarmed", "xuanfeng-leg");
	map_skill("strike" , "luoying-shenzhang");
	map_skill("dodge"  , "anying-fuxiang");
	map_skill("parry"  , "tanzhi-shentong");
	map_skill("sword"  , "yuxiao-jian");
	map_skill("chuixiao-jifa", "bihai-chaosheng");
	map_skill("throwing", "tanzhi-shentong");

	prepare_skill("finger" , "tanzhi-shentong");
	prepare_skill("hand"   , "lanhua-shou");

	set("no_teach", ([
		"bibo-shengong"   : (: try_to_learn_bibo :),
		"lanhua-shou"     : (: try_to_learn_lanhua :),
		"tanzhi-shentong" : (: try_to_learn_tanzhi :),
		"yuxiao-jian"     : (: try_to_learn_yuxiao :),
	]));

	set("inquiry", ([
		"����ɨҶ�ȷ�" : (: ask_me :),
		"�ؼ�"      : (: ask_me :),
		"�뵺"      : (: ask_leave :),
		"����"      : "���ֱ����Ů���Ĺ����� ",
		"�����澭"  : "������ܰ���ȡ���澭�ϲᣬ��һ������л�㡣",
		"������"    : "������Ѩ��... ������ϧ�Ҽ������Ӷ��㲻�óɲţ�",
		"��ָ��ͨ"  : "��... ��... һ����վ�Ȼ���˿��Լ̳У�",
		"��������"  : "����... �����������ˣ�����ܹ�����⽣����",
		"�̲���"  : "��... ���һ������ڹ��ε���������ϧ...",
		"����"      : "�Դ���(chuixiao-jifa)����Ȥô������ѧ�㣿",
		"����鳤"  : (: ask_qing :),
		"����"      : (: ask_qing :),
		"����"      : (: ask_qing :),
		"�һ�ҩ��"  : (: ask_medicine :),
		"��ҩ"      : (: ask_medicine :),
		"�Ż���¶��": "����������Ƶý�����ú�ѧѧ�һ�ҩ���Ժ��Լ��ưɡ�",
		"�޳���"    : "��...����ѧͨ���һ�ҩ��İ���Լ������ưɡ�",
		"����"      : (: ask_music_book :),
	]));

	create_family("�һ���", 1, "����");

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "sword.bihai" :),
		(: perform_action, "sword.qing" :),
		(: perform_action, "sword.tianwai" :),
		(: perform_action, "hand.fuxue" :),
		(: perform_action, "finger.jinglei" :),
		(: exert_function, "powerup" :),
		(: exert_function, "recover" :),
	}));

	set_temp("apply/attack", 150);
	set_temp("apply/defense", 150);
	set_temp("apply/damage", 100);
	set_temp("apply/unarmed_damage", 100);
	set_temp("apply/armor", 200);

	setup();

	set("book_count", 1);
	set("taohua_book", 1);
	set("music_book", 1);

	carry_object("/d/taohua/obj/yuxiao")->wield();
	carry_object("/d/taohua/obj/bupao")->wear();
}

int recognize_apprentice(object ob, string skill)
{
	if (skill == "chuixiao-jifa" ||
	    skill == "taohua-yuan")
	{
		if (! ob->query_temp("can_learn/huang/chuixiao-jifa"))
		{
			ob->set_temp("can_learn/huang/chuixiao-jifa", 1);
			command("say ���Ȼ�Դ�������Ȥ���Ҿͽ���һ��ɡ�");
		}
		return 1;
	}

	return 0;
}

mixed try_to_learn_bibo()
{
	object ob = this_player();

	if (ob->query("can_learn/huang/bibo-shengong"))
		return 0;

	if (ob->query_skill("luoying-xinfa", 1) >= 120)
	{
		command("say �������벻���ҵĵ�����˳�ɫ�����"
			"��Ӣ�ķ����������裬�Ҿʹ���̲��񹦰ɣ�");
		ob->set("can_learn/huang/bibo-shengong", 1);
		return 0;
	}

	return "�̲������Ҷ����ڹ����Ų��⴫��";
}

mixed try_to_learn_lanhua()
{
	object ob = this_player();

	if (ob->query("can_learn/huang/lanhua-shou"))
		return 0;

	if (ob->query_skill("bibo-shengong", 1) >= 100)
	{
		command("say ����������̲����Ѿ����л�"
			"���ˣ��Ҿʹ���������Ѩ�ַ��ɣ�");
		ob->set("can_learn/huang/lanhua-shou", 1);
		return 0;
	}

	return "������Ѩ�ֲ��⴫��";
}

mixed try_to_learn_tanzhi()
{
	object ob = this_player();

	if (ob->query("can_learn/huang/tanzhi-shentong"))
		return 0;

	return "��ѧ�ҳ����������ٺ�...";
}

mixed try_to_learn_yuxiao()
{
	object ob = this_player();

	if (ob->query("can_learn/huang/yuxiao-jian"))
		return 0;

	if (ob->query("couple"))
	{
		command("say ����Ҳ���������ˣ��ʹ������｣���ɣ�");
		ob->set("can_learn/huang/yuxiao-jian", 1);
		return 0;
	}

	return "������������ֻ������Ե�ˣ�";
}

void attempt_apprentice(object ob)
{
	string master;
	string *app = ({ "��Ĭ��", "½�˷�", "�����" });

	if (! permit_recruit(ob))
		return;

	if (ob->query_int() < 28)
	{
		command("say �Ҳ������ʲ�ĵ��ӣ�����ذɣ�");
		return;
	}

	if ((int)ob->query("shen") >100000 || (int)ob->query ("shen") < -100000 )
	{
		command("say ���һ��������������������������ֳ�������򽻵�������ذɣ�");
		return;
	}

	if (ob->query("combat_exp") < 200000)
	{
		if (stringp(master = ob->query_temp("taohua/master")))
		{
			command("say ���������" + master + "ѧ������������ô���£�");
			return;
		}

		if (ob->query("family/family_name") == "�һ���" &&
		    ob->query("family/master_name") != "��ҩʦ")
		{
			command("say �úú�" + ob->query("family/master_name") +
				"ѧ�գ���Ҫ���Ķ��⣬����һ��ˮƽ����Ȼ�����Ե㲦�㡣");
			return;
		}

		master = app[random(sizeof(app))];
		
		command("say ���������һ����ˣ���������ѧ����ɾ����ޣ��Ⱥ��ҵ���" +
			master + "ѧϰ�ɡ�");
		ob->set_temp("taohua/master", master);
		ob->set("family/family_name", "�һ���");
		return;
	}

	command("say �ܺã��ܺá�");
	command("recruit " + ob->query("id"));
}

string ask_me()
{
	object ob;
	
	if (this_player()->query("family/master_id")!="huang yaoshi")
		return RANK_D->query_respect(this_player()) + 
		"���ҵ��ӣ���֪�˻��Ӻ�̸��";
	if (query("book_count") < 1)
		return "�������ˣ����ɵ��ؼ����ڴ˴���";
	add("book_count", -1);
	ob = new("/clone/book/xuanfeng_book");
	ob->move(this_player());
	return "�ðɣ��Ȿ������ɨҶ�ȷ������û�ȥ�ú����С�";
}

int ask_leave()
{
	object me;

	me = this_player();
	if (me->query("family/family_name") == "�һ���")
	{
		message_vision("$N��$nŭ�������Ȼ�����һ������£�"
			       "�һ���Ͳ����˺��㣬Ҫ�뵺�Լ���ȥ���ߣ�\n",
				this_object(), me);
		return 1;
	}

	command("say �ðɣ��Ҿ�����һ�̡�");
	message_vision("$N˵�գ�һ������$n��ƨ���ϣ��ͼ�$nһ"
		       "��ƽɳ����ʽ���˳�ȥ��\n", this_object(), me);
	me->move("/d/taohua/haitan");
	message_vision("$Nһ��ˤ��ɳ̲�ϣ��ߺ�ѽѽ�����������\n", me);
	return 1;
}

mixed ask_qing()
{
	object me;

	me = this_player();
	if (me->query("can_perform/yuxiao-jian/qing"))
		return "��ú���ϰ�书����Ҫ���ҵ�����";

	if (me->query("family/family_name") != query("family/family_name"))
		return "�㲻�������һ������ˣ������ҵ��书��Ҫ��ʲô��";

	if (me->query_skill("yuxiao-jian", 1) < 100)
		return "������㱾�£���������｣���������������Ұɣ�";

	message_vision(HIC "$n" HIC "��ͷ���죬������˼�����ִ���$N"
		       HIC "�ļ�ͷ��$N" HIC "��Ȼ��������ԴԴ���ţ����ɴ󾪣�"NOR"\n",
		       me, this_object());
	command("sigh");
	command("say �㶮��ô��");
	tell_object(me, HIG "��ͨ��������鳤�İ��"NOR"\n");
	if (me->can_improve_skill("force"))
		me->improve_skill("force", 90000);
	me->set("can_perform/yuxiao-jian/qing", 1);
	me->set("neili", 0);
	return 1;
}

int ask_medicine()
{
	object me;
	object ob;

	me = this_player();
	if (me->query("family/family_name") != query("family/family_name"))
	{
		command("say ����ʲô�ˣ������ҵ�ҽ���к�Ŀ�ģ�");
		return 1;
	}

	if ((int)me->query_skill("taohua-yaoli", 1) < 100)
	{
		command("say ����һ�ҩ����˽�̫ǳ������ѧ����"
			"��һЩ�Ҳ��ܰ��ر������㡣");
		return 1;
	}

	if (query("taohua_book") < 1)
	{
		command("say ���ǿ�ϧ���������ˣ������Ѿ����ȥ�ˡ�");
		return 1;
	}

	add("taohua_book", -1);
	ob = new("/clone/book/taohua");
	message_vision("$n�ó�һ�����Ƶı����ӵݸ�$N������"
		       "���������Ҫ���Һú��ж�����\n",
		       me, this_object());
	ob->move(me, 1);
	return 1;
}

int accept_object(object who, object ob)
{
	int r;

	if (r = ::accept_object(who, ob))
		return r;

	if (ob->query("id") == "jiuyin zhenjing2")
	{
		destruct(ob);
		command("sigh");
		if (who->is_apprentice_of(this_object()))
		{
			if (who->query("can_learn/huang/tanzhi-shentong"))
				return 1;
			command("say ��...�ã��������ҵĺ�ͽ��������... ����");
			command("look " + who->query("id"));
			if (who->query("combat_exp") < 500000)
			{
				command("say �ҵ������һ�ž�������ϧ"
					"�������书̫����鲻�㣬�����Ժ���˵�ɣ�");
				return 1;
			}
			command("haha");
			command("say ���书��Ȼ�����ã��Ҿʹ��㵯ָ"
				"��ָͨ������Ҫ�ú�ѧϰ���ž�����");
			who->set("can_learn/huang/tanzhi-shentong", 1);
			return 1;
		}
		message_vision("$N��$n������л��λ" +
			       RANK_D->query_respect(who) + "�ˡ�\n",
			       this_object(), who);
		return 1;
	}

	return 0;
}

mixed ask_music_book()
{
	object me;
	object ob;

	me = this_player();
	if (query("music_book") < 1)
		return "�ҵ������Ѿ����ȥ�ˡ�\n";

	ob = new("/clone/book/xiaopu");
	ob->move(me, 1);
	message_vision("$n�����׸���$N����������ȥ�Լ��ú��о��ɡ�\n",
		       me, this_object());
	set("music_book", 0);
	return 1;
}

void reset()
{
	set("music_book", 1);
	set("book_count", 1);
	set("taohua_book", 1);
}

void unconcious()
{
	die();
}
