// longcheng.c Ľ������

#include <ansi.h>

inherit NPC;

mixed ask_me();
mixed try_learn_sk();

void create()
{
	set_name("Ľ������", ({ "murong longcheng", "murong", "longcheng" }));
	set("long", @LONG
���ǹ���Ľ�ݵĴ��ˣ�һ�ִ����˾����书��ת���ƣ��Ӷ�
ʹĽ�ݼ�����Ϊ�������ҵ�λ��
LONG );
	set("gender", "����");
	set("age", 54);
	set("attitude", "peaceful");

	set("str", 32);
	set("int", 39);
	set("con", 33);
	set("dex", 34);

	set("qi", 6000);
	set("max_qi", 6000);
	set("jing", 3000);
	set("max_jing", 3000);
	set("neili", 7200);
	set("max_neili", 7200);
	set("jiali", 90);

	set("combat_exp", 2700000);

	set_skill("force", 200);
	set_skill("literate", 150);
	set_skill("unarmed", 200);
	set_skill("cuff", 200);
	set_skill("finger", 200);
	set_skill("sword", 200);
	set_skill("blade", 200);
	set_skill("dodge", 200);
	set_skill("parry", 200);

	set_skill("zihui-xinfa", 200);
	set_skill("douzhuan-xingyi", 200);
	set_skill("beidou-xianzong", 200);
	set_skill("canhe-zhi", 200);
	set_skill("qixing-quan", 200);
	set_skill("murong-sword", 200);
	set_skill("longcheng-shendao", 200);

	map_skill("force", "zihui-xinfa");
	map_skill("dodge", "beidou-xianzong");
	map_skill("cuff",  "qixing-quan");
	map_skill("parry", "douzhuan-xingyi");
	map_skill("finger", "canhe-zhi");
	map_skill("sword", "murong-sword");
	map_skill("blade", "longcheng-shendao");

	prepare_skill("finger", "canhe-zhi");
	prepare_skill("cuff", "qixing-quan");

	set("inquiry", ([
		"����"   : (: ask_me :),
		"����"   : (: ask_me :),
		"���꽻��": (: ask_me :),
	]));

	create_family("Ľ������", 12, "����");
	set("chat_chance", 1);
	set("chat_msg",({
		"Ľ�����ǵ�ͷ���\n",
	}));

	setup();
	carry_object("/clone/weapon/gangdao")->wield();
	carry_object("/clone/misc/cloth")->wear();
	add_money("silver", 10);
}

void attempt_apprentice(object ob)
{
	if (ob->query("family/family_name") == query("family/family_name"))
	{
		command("say ����Ͳ���ͽ���ˣ�������Ҳ������"
			"Ľ�ݼҵĴ��ˣ��Ҿʹ���һ�׵���(longcheng-shendao)�ɣ�");
	} else
		command("say �Ҳ���ͽ�ܡ�");
}

int recognize_apprentice(object ob)
{
	return ob->query("family/family_name") == query("family/family_name");
}

mixed ask_me()
{
	object me;

	me = this_player();
	if (me->query("can_perform/longcheng-shendao/fengyu"))
		return "�ú������ɣ��⸴����Ϳ�����������������";

	if (me->query("family/family_name") != query("family/family_name"))
		return "�����Ķ����ģ��ҿɲ���ʶ�㡣";

	if (me->query_skill("longcheng-shendao", 1) < 120)
		return "��ѧ���꽻�����ȿɵ������ҵ������񵶰���";

	message_vision(HIC "$n" HIC "����������һ�����ӣ�����һ��������"
		       "��ñ�ֱ���漴������$N" HIC "ֻ�ܿ��õ��ǹ��㡣\n$n"
		       HIC "�����ջص��ƣ��������������嵶��$N"
		       HIC "���˲�����Ȼ����"NOR"\n",
		       me, this_object());
	command("say ֪���˰ɣ�");
	tell_object(me, HIG "��ѧ���˷��꽻�ӡ�"NOR"\n");
	if (me->can_improve_skill("blade"))
		me->improve_skill("blade", 160000);
	me->set("can_perform/longcheng-shendao/fengyu", 1);
	return 1;
}
