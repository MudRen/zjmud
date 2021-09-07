// xiaozhao.c
#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;

int ask_tuijiao();
int ask_wuji();
int ask_jian();
int ask_gold();
int ask_ge();
int ask_qiankun();

void create()
{
	set_name("С��", ({ "xiao zhao", "xiao", "zhao" }));
	set("nickname", HIC "����˼��������" NOR);
	set("long",
	    "��˫Ŀտտ������ü�˱ǣ��ձ�΢�����У������������ף�ֻ�������\n"
	    "С�������δ���ɣ���Ȼ��ò������ȴ�ڲ�ס�����е�������\n");
	set("gender", "Ů��");
	set("age", 15);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("per", 30);
	set("str", 15);
	set("int", 25);
	set("con", 25);
	set("dex", 30);

	set("max_qi", 500);
	set("max_jing", 200);
	set("max_neili", 500);
	set("jiali", 50);
	set("combat_exp", 50000+random(10000));
	set("score", 20000);

	set_skill("force", 80);
	set_skill("dodge", 80);
	set_skill("unarmed", 80);
	set_skill("sword", 80);
	set_skill("taiji-jian", 70);
	set_skill("taiji-quan", 70);
	set_skill("tiyunzong",50);
	map_skill("dodge", "tiyunzong");
	map_skill("parry", "taiji-jian");
	map_skill("sword", "taiji-jian");
	map_skill("unarmed", "taiji-quan");

	set_temp("apply/attack", 15);
	set_temp("apply/damage", 15);
	set("party/party_name", HIG "����" NOR);
	set("party/rank", HIG "��˹ʥ����" NOR);
	set("party/level", 1);
	set("inquiry", ([
	    "�˽�" :    (: ask_tuijiao :),
	    "���޼�" :  (: ask_wuji :),
	    "���콣" :  (: ask_jian :),
	    "�ƽ�" :    (: ask_gold :),
	    "��" :      (: ask_ge :),
	    "Ǭ����Ų��": (: ask_qiankun :),
	    "Ǭ����Ų���ķ�": (: ask_qiankun :),
	]));

	set("chat_chance", 3);
	set("chat_msg", ({
		    "С�ѵ�������������˼�������� �䵱ɽ���ɰس�\n",
		    "С�ѵ����������������������� ����ɥ��������\n",
		    "С�ѵ���������������÷��ױ ��鶱��麣ãã\n",
		    "С�ѵ���������˭�ͱ��������� �ʮ�ط��麽\n",
		    "С�ѵ��������������ۻ���δ�� ��������ݸγ�\n",
		    "С�ѵ�����������Ů��������ǹ �������ҩ����\n",
		    "С�ѵ���������������������ǽ ����ʱ����ɽ��\n",
		    "С�ѵ�����������ı�����һ�� ���������ξ���\n",
		    "С�ѵ��������������ûһЦ�� ���쳤���ɺ�â\n",
		    "С�ѵ���������������ǽ�ƽ��� ���ӹ�Ѩ�����\n",
		    "С�ѵ������������ѽ�׵���ǿ Ⱥ�۹���Լ����\n",
		    "С�ѵ�����������ܽ�������ׯ ̫��������˸�\n",
		    "С�ѵ����������ٻ�����λͻ� ��ò���������\n",
		    "С�ѵ����������ٳ߸����λ��� �������������\n",
		    "С�ѵ�����������Ůͬ�ۺ����� �������������\n",
		    "С�ѵ���������������ʧ������ ԩ�ɲ��׳�����\n",
		    "С�ѵ����������ﳤ�ٶ������� �¸������Ѻ���\n",
		    "С�ѵ�����������ʨ�л���Ϊ�� ز�����������\n",
		    "С�ѵ�������������Ӣ��Ī�ܵ� ���ӿ���֮�Է�\n",
		    "С�ѵ������������ű�����в� ��ʶ����������\n",
	}) );

	setup();
	carry_object("/clone/misc/cloth")->wear();
}

int ask_tuijiao()
{
	object ob;
	ob=this_player();

	if (ob->query("party/party_name") != "����")
	{
	    message_vision("С��ݸ��һЦ����$N˵�����㻹û������"
			   "�����أ������˽̣�\n",ob);
	    return 1;
	}

	command("look "+ob->query("id"));
	command("sigh ");
	command("nod ");
	ob->delete("party");
	ob->delete("rank");
	ob->delete("level_mj");
	return 1;
}

int ask_wuji()
{
	command("sigh " + this_player()->query("id"));
	say("С�����ĵ�˵������˼����������������������̡�\n");
	return 1;
}

int ask_jian()
{
	command("say �Ҳ�֪��������...�����ҡ�");
	return 1;
}

int ask_gold()
{
	command("say ���а����ⲻ�������ˡ�");
	return 1;
}

int ask_ge()
{
	command("nod "+this_player()->query("id"));
	say("С������������\n\n" +
	"����������  ����������\n\n"+
	"���˼�������˷�  ������ �ײؼ�  �������ܳ�����\n\n"+
	"��ӯ�  ������ʴ  ���¶���  �������  �����������\n\n"+
	"չ�ų�ü  ��������  ��������  ��������  ��������  �������\n\n"+
	"�����͵��޵�  ƶ�ĺ͸���  ��ͷ��һ��  ������һ��\n\n"+
	"������һ��  һ������\n\n"+
	"�������  ��ʮ��ϡ  ��������  ������ˮ\n\n");
	return 1;
}

int ask_qiankun()
{
    	command("say ���ϴ���������������ʧ�٣�Ǭ����Ų���ķ�"
		"�Ѿ�ʧ��ܾ��ˡ�\n");
	command("say �����Ź��Ӳ����ܵ��������˻�����\n");
	return 1;
}
