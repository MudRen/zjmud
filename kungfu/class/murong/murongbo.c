// murongbo.c Ľ�ݲ�

#include <ansi.h>
#include "murong.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_COAGENT;

mixed ask_me();
mixed try_learn_sk();

string ask_book1();
string ask_book2();
mixed  ask_martial();

void create()
{
	set_name("Ľ�ݲ�", ({ "murong bo", "murong", "bo" }));
	set("long", @LONG
���ǹ���Ľ�ݵĴ��ˣ�����˵����Ľ�����������书��Ϊ�ܳ�
֮�ˡ������ܹ�ͨ���°ټ�֮����������Ϊ��ͨĽ�ݼҾ�����
LONG );
	set("nickname", HIM "�Ա�֮�� ��ʩ����" NOR);
	set("gender", "����");
	set("age", 54);
	set("shen_type",-1);
	set("attitude", "peaceful");

	set("str", 31);
	set("int", 37);
	set("con", 34);
	set("dex", 33);

	set("qi", 5700);
	set("max_qi", 5700);
	set("jing", 2800);
	set("max_jing", 2800);
	set("neili", 7000);
	set("max_neili", 7000);
	set("jiali", 125);

	set("combat_exp", 2650000);

	// base skill
	set_skill("force", 270);
	set_skill("literate", 220);
	set_skill("unarmed", 260);
	set_skill("cuff", 270);
	set_skill("finger", 270);
	set_skill("strike", 260);
	set_skill("hand", 260);
	set_skill("claw", 260);
	set_skill("club", 260);
	set_skill("sword", 270);
	set_skill("blade", 260);
	set_skill("staff", 260);
	set_skill("dodge", 260);
	set_skill("parry", 270);

	// shaolin skill. No teach
	set_skill("banruo-zhang", 250);
	set_skill("cibei-dao", 250);
	set_skill("damo-jian", 250);
	set_skill("fengyun-shou", 250);
	set_skill("fumo-jian", 250);
	set_skill("hunyuan-yiqi", 250);
	set_skill("shaolin-xinfa", 250);
	set_skill("jingang-quan", 250);
	set_skill("longzhua-gong", 250);
	set_skill("luohan-quan", 250);
	set_skill("nianhua-zhi", 250);
	set_skill("pudu-zhang", 250);
	set_skill("qianye-shou", 250);
	set_skill("sanhua-zhang", 250);
	set_skill("riyue-bian", 250);
	set_skill("shaolin-shenfa", 250);
	set_skill("weituo-gun", 250);
	set_skill("wuchang-zhang", 250);
	set_skill("xiuluo-dao", 250);
	set_skill("yingzhua-gong", 250);
	set_skill("yizhi-chan", 250);
	set_skill("zui-gun", 250);

	// murong skill
	set_skill("zihui-xinfa", 270);
	set_skill("douzhuan-xingyi", 270);
	set_skill("beidou-xianzong", 270);
	set_skill("canhe-zhi", 270);
	set_skill("qixing-quan", 270);
	set_skill("murong-sword", 270);
	set_skill("martial-cognize", 200);

	map_skill("force", "zihui-xinfa");
	map_skill("dodge", "beidou-xianzong");
	map_skill("cuff",  "qixing-quan");
	map_skill("parry", "douzhuan-xingyi");
	map_skill("finger", "canhe-zhi");
	map_skill("sword", "murong-sword");

	prepare_skill("finger", "canhe-zhi");
	prepare_skill("cuff", "qixing-quan");

	set("no_teach", ([
		"banruo-zhang"  : (: try_learn_sk :),
		"cibei-dao"     : (: try_learn_sk :),
		"damo-jian"     : (: try_learn_sk :),
		"fengyun-shou"  : (: try_learn_sk :),
		"fumo-jian"     : (: try_learn_sk :),
		"hunyuan-yiqi"  : (: try_learn_sk :),
		"shaolin-xinfa" : (: try_learn_sk :),
		"jingang-quan"  : (: try_learn_sk :),
		"longzhua-gong" : (: try_learn_sk :),
		"luohan-quan"   : (: try_learn_sk :),
		"nianhua-zhi"   : (: try_learn_sk :),
		"pudu-zhang"    : (: try_learn_sk :),
		"qianye-shou"   : (: try_learn_sk :),
		"sanhua-zhang"  : (: try_learn_sk :),
		"riyue-bian"    : (: try_learn_sk :),
		"shaolin-shenfa": (: try_learn_sk :),
		"weituo-gun"    : (: try_learn_sk :),
		"wuchang-zhang" : (: try_learn_sk :),
		"xiuluo-dao"    : (: try_learn_sk :),
		"yingzhua-gong" : (: try_learn_sk :),
		"yizhi-chan"    : (: try_learn_sk :),
		"zui-gun"       : (: try_learn_sk :),
	]));

	set("inquiry", ([
		"��ת����" : (: ask_me :),
		"�ϻ��ķ�" : (: ask_book1 :),
		"��ת����" : (: ask_book2 :),
		"��ѧ����" : (: ask_martial :),
	]));

	set("zihui_count", 1);
	set("douzhuan_count", 1);

	create_family("Ľ������", 15, "����");
	set("chat_chance", 1);
	set("chat_msg", ({
		"Ľ�ݲ���̾��������... ���డ��\n",
	}));

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: exert_function, "powerup" :),
		(: exert_function, "recover" :),
		(: perform_action, "finger.ci" :),
		(: perform_action, "finger.lian" :),
		(: perform_action, "finger.zhi" :),
	}));

	set_temp("apply/attack", 150);
	set_temp("apply/defense", 150);
	set_temp("apply/damage", 100);
	set_temp("apply/unarmed_damage", 100);
	set_temp("apply/armor", 200);

	setup();
	carry_object("/clone/misc/cloth")->wear();
	add_money("silver", 10);
}

void attempt_apprentice(object ob)
{
	if(! permit_recruit(ob))
		return;

	if((int)ob->query("combat_exp") < 200000)
	{
		if (random(2))
			command("smile");
		else
			command("pat " + ob->query("id"));

		command("say ��ľ��黹�������Ⱥ��Ҷ�Ľ�ݸ�ѧϰ�ɣ�");
		return ;
	}

	command("haha");
	command("pat " + ob->query("id"));
	command("recruit " + ob->query("id"));
	message_vision("Ľ�ݲ���ϲ������Ľ�ݼ�����Ӣ�ŵ�����������������\n",
		       this_object());
	return;
}

mixed try_learn_sk()
{
	object me;

	me = this_player();
	if (me->query_temp("has_asked/murongbo"))
		return "�㻹�ǰ���ѧ���Ź���ɡ�";

	command("shake");
	command("say ��˵���ֵ��书ѧ�˶������к�����Ͳ�Ҫѧ�ˡ�");
	me->set_temp("has_asked/murongbo", 1);
	return -1;
}

mixed ask_me()
{
	object me;

	me = this_player();
	if (me->query("can_perform/douzhuan-xingyi/yi"))
		return "�㻹����ȥ����ȥ���⸴���಻�ǿ�����˵�ģ�";

	if (me->query("family/family_name") != query("family/family_name"))
		return "����ʲô�ˣ��кξ��ģ�";

	if (me->query_skill("douzhuan-xingyi", 1) < 100)
		return "��ת����������Ľ�ݼҵľ�ѧ��������û�У�";

	message_vision(HIY "$n" HIY "����$N" HIY "��ʾ��$N"
		       HIY "���Լ�һ�У�$N" HIY "���ɻ���"
		       "�ĳ�һ�ƣ�ֻ��$n" HIY "��������һ����"
		       HIY "$N����ʽ����\n��Ȼ��䣬����������"
		       "�������һ����һ�ƽ��ʵʵ�Ĵ�����$P"
		       HIY "�Լ��ļ�ͷ��"NOR"\n",
		       me, this_object());
	command("nod");
	command("say �����еİ����������������ʽ�����"
		"Ľ�ݼҵ��ϻ��ķ�����Ҫ�ú���ᣬȥ�ɣ�");
	tell_object(me, HIG "��ѧ���˶�ת���ơ�"NOR"\n");
	if (me->can_improve_skill("douzhuan-xingyi"))
		me->improve_skill("douzhuan-xingyi", 90000);
	if (me->can_improve_skill("zihui-xinfa"))
		me->improve_skill("zihui-xinfa", 90000);
	me->set("can_perform/douzhuan-xingyi/yi", 1);
	return 1;
}

string ask_book1()
{
	mapping fam; 
	object ob;
	object me;

	me = this_player();
	if (me->query("family/family_name") != query("family/family_name"))
		return RANK_D->query_respect(me) + 
		       "����Ľ�ݼ�������������֪�˻��Ӻ�̸��";

	if (me->query_skill("zihui-xinfa", 1) < 100)
		return "����ϻ��ķ�ˮƽ�����������ò����Ȿ�ؼ���";

	if (query("zihui_count") < 1)
		return "�������ˣ��ϻ��ؼ����Ѿ����ȥ�ˡ�";

	add("zihui_count", -1);
	ob = new("/clone/book/zihui-book");
	ob->move(me, 1);
	return "�ðɣ��Ȿ�ϻ��ķ�����ȥ�ú��ж���";
}

string ask_book2()
{
	object ob;
	object me;

	me = this_player();
	if (me->query("family/family_name") != query("family/family_name"))
		return RANK_D->query_respect(this_player()) + 
		       "����Ľ�ݼ�������������֪�˻��Ӻ�̸��";

	if (me->query_skill("douzhuan-xingyi", 1) < 100)
		return "��Ķ�ת�������Ļ������ң��һ����ܸ����Ȿ�ؼ���";

	if (query("douzhuan_count") < 1)
		return "�������ˣ��ؼ����Ѿ����ȥ�ˡ�";

	add("douzhuan_count", -1);
	ob = new("/clone/book/douzhuan-book");
	ob->move(me, 1);
	return "�Ȿ��ת����������պ��ˡ�";
}

mixed ask_martial()
{
	object ob;
	object me;

	me = this_player();
	if (me->query("family/family_name") != query("family/family_name"))
		return RANK_D->query_respect(me) +
		       "������������Լ�Ҫ�ڼ���������";

	if (me->query("combat_exp") < 200000)
		return "������书Ҳ�����������ѧ����úø�������ȥ��";

	if (me->query_skill("martial-cognize", 1) < 50)
		return "�������ѧ�������������������̸���а��";

	if (me->query_skill("martial-cognize", 1) >= 200)
		return "����ѧ�˽���Ѿ������ˣ�����ûʲô���ٽ�����ˡ�";

	if (me->query_temp("last_ask/murongbo/martial") + 240 > time())
		return "������̸�ɣ�������Ҫ�����룬�ú������ᡣ";

	message_vision("$N����$n���������ðɣ��Ҿ�����̸̸��Ľ�ݼ�����ѧ������ĵá���\n",
		       this_object(), me);
	if (me->query("potential") - me->query("learned_points") < 100)
	{
		tell_object(me, "���������Ժ����ģ�û����������Ȼ��������Ǳ�ܲ�����\n");
		return 1;
	}

	me->add("learned_points", 100);
	tell_object(me, HIG "���������л�Ȼ���ʣ�ͨ���˲�����ѧ�İ��"NOR"\n");
	me->set_temp("last_ask/murongbo/martial", time());
	me->improve_skill("martial-cognize", 2000 + random(1000));
	return 1;
}

void reset()
{
	set("zihui_count", 1);
	set("douzhuan_count", 1);
}

void unconcious()
{
	die();
}
