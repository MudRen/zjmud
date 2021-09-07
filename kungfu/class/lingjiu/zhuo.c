// zhuo.c ׿����

#include <ansi.h>;

inherit NPC;

mixed ask_me();

void create()
{
	set_name("׿����", ({ "zhuo bufan", "zhuo", "bufan"}));
	set("gender", "����");
	set("title", "һ�ֻ۽�������");
	set("nickname", HIY "����" NOR);
	set("age", 37);
	set("long", @LONG
��ʮ����ǰ��һ�ֻ۽�������ʦͽ��ͯ��ɱ�þ��⣬��ʱ׿��
�����ڸ������������ѣ��Ӵ���Ҳ���һ�ȥ���ӵ�����ɽ�л�Ƨ��
��֮�ؿ��н����������е���ǰ��������������һ��������������
ʮ�꣬���ڽ�����ɣ����������޵С�
LONG );
	set("attitude", "peaceful");
	set("str", 32);
	set("int", 31);
	set("con", 33);
	set("dex", 31);
    
	set("qi", 4500);
	set("max_qi", 4500);
	set("jing", 2200);
	set("max_jing", 2200);
	set("neili", 4800);
	set("max_neili", 4800);
	set("jiali", 120);
	set("combat_exp", 2200000);

	set_skill("force", 220);
	set_skill("hunyuan-yiqi", 220);
	set_skill("sword", 230);
	set_skill("zhougong-jian", 230);
	set_skill("dodge", 210);
	set_skill("feiyan-zoubi", 210);
	set_skill("strike", 225);
	set_skill("liuyang-zhang", 225);
	set_skill("parry", 230);

	map_skill("force", "hunyuan-yiqi");
	map_skill("sword", "zhougong-jian");
	map_skill("dodge", "feiyan-zoubi");
	map_skill("parry", "zhougong-jian");
	map_skill("strike", "liuyang-zhang");

	prepare_skill("strike", "liuyang-zhang");

	set("inquiry", ([
		"��â"     : (: ask_me :),
		"����"     : (: ask_me :),
		"��ɽͯ��" : "��ɱ����һ�ֻ۽�������ʦͽ���ҿ��������磿",
		"����"     : "�����������չ��µ�����������ȫ���������",
		"������"   : "�����������չ��µ�����������ȫ���������",
		"����"     : "�ҵ��ܹ���������˫������������û�ڶ����ܹ��й���",
	]));

	set("chat_chance_combat", 40);
	set("chat_msg_combat", ({
		(: perform_action, "sword.mang" :),
		(: exert_function, "recover" :),
	}) );

	setup();
	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/clone/cloth/cloth")->wear();
}

int recognize_apprentice(object ob, string skill)
{
	if (interactive(ob) && (!ob->query("family") ||
	   ob->query("family")["master_name"] != "����"))
	{
		command("heng");
		command("say ����ʲô����������ϰ�Ҿ���Ľ�����\n");
		return -1; 

	}
	if (skill != "zhougong-jian" && skill != "sword")
	{
		command("shake");
		command("say �Һųƽ���Ҳֻ�ܴ�����һЩ������");
		return -1;
	}
	if (! ob->query_temp("can_learn/zhuobufan"))
	{
		command("say �ã����Ȼ����Ȥ�����������ĵ��ӣ��Ҿͽ��������ܹ�����");
		ob->set_temp("can_learn/zhuobufan", 1);
	}
	return 1;
}

mixed ask_me()
{
	object me;

	me = this_player();
	if (me->query("can_perform/zhougong-jian/mang"))
		return "�Լ��úö���ϰ�ɣ�";

	if (me->query("family/master_name") != "����" ||
	    me->query("family/master_id") != "xu zhu")
		return "���⻰��ʲô��˼��";

	if (me->query_skill("zhougong-jian", 1) < 120)
		return "����ܹ����������ң�Ҫ��������";

	if ((int)me->query("max_neili", 1) < 1500)
		return "��������Ϊ̫���ˣ�������ϰ�ߵ������ɡ�\n";

	message_vision(HIY "$n" HIY "���˵�ͷ���γ������彣������һ"
		       "ͦ��������ͻȻ����������²�������â��\n����"
		       "������磬һչ���߷緶��$N" HIY
		       "Ŀ��һ�����ƺ�������ʲô��"NOR"\n",
		       me, this_object());

	command("haha");
	command("say ������ˣ��������������߾��硪����â���Լ���ȥ���о��о��ɡ�");
	tell_object(me, HIC "��ѧ����ʹ�ý�â��"NOR"\n");
	if (me->can_improve_skill("sword"))
		me->improve_skill("sword", 160000);
	me->set("can_perform/zhougong-jian/mang", 1);
	return 1;
}

