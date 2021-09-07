#include <ansi.h>
inherit NPC;
inherit F_UNIQUE;
inherit F_MASTER;
int ask_weiwang();

void create()
{
	set_name("����", ({ "fan gang", "fan" }));
	set("title", HIR "��ػ�"HIG"��ľ��"NOR"����"); 
	set("shen_type", 1);
	set("gender", "����");
	set("age", 35);
	set("long",
		"\n��������ػ���ľ�õķ��٣��͹ذ������͡�\n");

	set_skill("unarmed", 60);
	set_skill("dodge", 70);
	set_skill("parry", 70);
	set_skill("sword", 80);
	set_skill("force", 70);
	set_skill("huashan-xinfa", 50);
	set_skill("huashan-sword", 70);
	set_skill("huashan-shenfa",60);
	map_skill("dodge", "huashan-shenfa");
	map_skill("parry", "huashan-sword");
	map_skill("sword", "huashan-sword");
	map_skill("force", "huashan-xinfa");

	set_temp("apply/attack", 35);
	set_temp("apply/attack", 35);
	set_temp("apply/damage", 25);

	set("combat_exp", 50000);
	set("attitude", "friendly");

	set("inquiry", ([
		"�½���" :  "\n����ܶ����ɲ����װ���\n",
		"��ػ�" :  "\nֻҪ��Ӣ�ۺú���������������ػ�(join tiandihui)��\n",
		"����" :  "\nֻҪ��������ػᣬ��ҾͿ���һ���ิ����\n",
		"���" :  "\nֻҪ��������ػᣬ��ҾͿ���һ���ิ����\n",
		"���帴��" : "ȥ���׳��͹ײĵ���ϸ���ưɣ�\n",
		"����" :  (: ask_weiwang :),
		"��������" : (: ask_weiwang :),
       ]) );

	setup();
	carry_object("/clone/misc/cloth")->wear();
	carry_object("/clone/weapon/changjian")->wield();
}


void init()
{
add_action("do_join","join");
}

void die()
{
message_vision("\n$N��ŭ��������ҿ����ӣ��ֵ��ǻ����ұ���ģ���˵�굹�����ˡ�\n", this_object());
::die();
}

int ask_weiwang()
{
command("tell "+this_player()->query("id")+" �����ڵĽ��������� " +(string)(this_player()->query("weiwang")));
say("\n����˵�����������ֵ�ܸߣ���Щ�˼����㲻������ɱ�㣬��������书�����㱦����\n"
+"�����㻹���Լ����ᣬ�������ȥ����Ŀ�꣬����ȥǮׯȡǮҲ������Ϣ ����������\n");
say("������˵��ɱĳЩ���˻��ĳЩ���˿�����߽���������\n");
return 1;
}
#include "/kungfu/class/yunlong/tiandihui.h";

