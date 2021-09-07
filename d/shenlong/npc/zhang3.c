// zhang3.c

#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;
inherit F_MASTER;
int do_skills(string arg);
int do_join(string arg);

void create()
{
	set_name("������", ({ "zhang laosan", "zhang" }));
	set("title", HIY"������"NOR"СͷĿ");
	set("gender", "����");
	set("age", 44);
	set("str", 25);
	set("dex", 20);
	set("long", "����һ��������ͷ��һ˫С�۾��������⡣\n");
	set("combat_exp", 25000);
	set("score", 2000);
	set("shen_type", -1);
	set("attitude", "peaceful");

	set_skill("force", 50);
	set_skill("unarmed", 70);
	set_skill("dodge", 70);
	set_skill("parry", 70);
	set_skill("yixingbu", 40);
	set_skill("shenlong-bashi", 50);
	map_skill("parry", "shenlong-bashi");
	map_skill("dodge", "yixingbu");

	set_temp("apply/attack", 15);
	set_temp("apply/defense", 15);
	set_temp("apply/armor", 10);
	set_temp("apply/damage", 10);
	set("neili", 500); 
	set("max_neili", 500);
	set("jiali", 10);
	set("inquiry", ([
		"������" : "һ�������벻���������̵�(join shenlongjiao)��",
		"���"   : "һ�������벻���������̵�(join shenlongjiao)��",
		"�鰲ͨ" : "����Ƣ�����ã�Ҫ�������Ĳźá�",
		"����"   : "����Ƣ�����ã�Ҫ�������Ĳźá�",
		"�ں�"   : "���겻�ϣ������ɸ����������룡������ʥ��",
	]));
	set("chat_msg", ({
"�����������е���������ѵ��ʱ�����ģ������˵У����²��ɣ�\n",
"�����������е�����־���Ŀɳɳǣ����������ޱ��ף�\n",
"�����������е����������������������������ǰ˷���\n",
"�����������е����˷����˳�Ӣ����������ͬ���¹⣡\n",
"�����������е������������ɸ����������룡\n",
	}) );
	setup();
	carry_object("/clone/misc/cloth")->wear();
}

void init()
{
	add_action("do_join", "join");
}

#include "/kungfu/class/shenlong/shenlong.h"
