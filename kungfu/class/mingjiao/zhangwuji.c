//zhangwuji.c

inherit F_MASTER;
inherit F_UNIQUE;
inherit NPC;

#include <ansi.h>
#include "mingjiao.h"

void greeting(object ob);

void create()
{
    seteuid(getuid());
    set_name("���޼�", ({ "zhang wuji", "zhang", "wuji" }));
    set("long", @LONG
���̽������޼ɣ�ͳ������ʮ����ڣ��������ƣ�߳��ǧ�
�������񹦡�����Ǭ����Ų�ơ��������£��ǽ����в�������
����Ӣ�ۡ�
LONG );
    set("title",HIG "����" HIM " ����" NOR);
    set("gender", "����");
    set("age", 20);
	set("no_get", 1);
    set("shen_type",1);
    set("attitude", "friendly");
    set("class", "fighter");

    set("str", 33);
    set("int", 35);
    set("con", 38);
    set("dex", 33);

    set("qi", 5800);
    set("max_qi", 5800);
    set("jing", 2700);
    set("max_jing", 2700);
    set("neili", 8000);
    set("max_neili", 8000);
    set("jiali", 120);

    set("combat_exp", 2900000);
    set("score", 455000);
    
    set_skill("force", 340);
    set_skill("unarmed", 200);
    set_skill("dodge", 200);
    set_skill("parry", 300);
    set_skill("sword", 260);
    set_skill("jiuyang-shengong", 340);
    set_skill("qiankun-danuoyi", 350);
    set_skill("qishang-quan", 250);
    set_skill("taiji-quan", 250);
    set_skill("taiji-jian", 260);
    set_skill("shenghuo-ling", 220);

    map_skill("force", "jiuyang-shengong");
    map_skill("dodge", "qiankun-danuoyi");
    map_skill("unarmed", "taiji-quan");
    map_skill("sword", "shenghuo-ling");
    map_skill("parry", "qiankun-danuoyi");

    create_family("����", 34, "����");

    set("chat_chance", 1);
    set("chat_msg", ({
	"���޼ɷ�Ȼ˵�������ɷ��Թ�Ϊ��, ����ɳ��, ��Ԫ��ҵδ��, ͬ������Ŭ��!��\n",
	"���޼�̾��������ʧһ֪��, ����λ�, �������, ����, ��������?��\n",
	"���޼ɵ����ҽ��ֵ�����: ��������, ���˼�Ϊ��, ��������, ������ħ!��\n",
    }));

    set("inquiry",([
	  "����" :     "���������������ʲô����\n",
	  "��ëʨ��" : "�������常л������ְ˾��\n",
	  "лѷ" :     "���������常�Ĵ�š�\n",
	  "�Ŵ�ɽ" :   "�������Ҹ���������? \n",
	  "������" :   "����������������΢������\n",
	  "������" :   "��̫ʦ�������ɺ�? \n",
	  "����" :     "����ʧһ֪��, ����λ�, �������, ����, ��������?\n",
	  "С��" :     "С���ҿ�һֱ�������ĺô���\n",
	  "������" :   "������ȥ����ɽ, �������ҡ�\n",
    ]));
    setup();
    add_money("silver", 70);
}

void init()
{
	object ob;

	::init();

	if (interactive(this_player()) && this_player()->query_temp("fighting"))
	{
		COMBAT_D->do_attack(this_object(), this_player(), query_temp("weapon"));
		this_player()->add_temp("beat_count", 1);
	}       
	if (interactive(ob=this_player()) && ! is_fighting())
	{
		remove_call_out("greeting");
		call_out("greeting",1,ob);
	}
}

void greeting(object ob)
{
	if (! ob || environment(ob)!=environment()) return;
	if ((int)ob->query("shen") < -50000)
	{
		command("wield yitian jian");
		command("hit" + (string)ob->query("id"));
		command("unwield yitian jian");
	} else
	if ((int)ob->query("shen") < -5000)
	{
		command("say ħ����������ѧ������������Ȱ������������"
			"���سɷ�");
	} else
	if((int)ob->query("shen") < -100)
	{
		command("say ��λ���ѣ����н��������е����������߽�аħ�����");
	} else
	if((int)ob->query("shen") >= 0)
	{
		command("say �������������ߣ�Ȱ����ӱ��ء�");
	} else
	if((int)ob->query("shen") > 50000)
	{
		command("say �������ϣ����޼�һ�񣬴������ձ�Ϊ�����̳���");
	}
	return;
}

int accept_fight(object ob)
{
	if ((ob->query("combat_exp") < 30000) && (ob->query("shen") > 0))
	{
		message_vision("�������������ǿ���ݣ��㲻���ҵĶ��֣�"
			       "��ȥ�ɡ�\n",ob);
		return 0;
	}
	message_vision("���޼�һ����˵������λ" + RANK_D->query_respect(ob) +
		       "����������ˡ�\n", ob);
	return 1;
}
