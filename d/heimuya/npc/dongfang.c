// dongfang.c

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
    set_name("��������", ({"dongfang bubai", "dongfang", "bubai"}));
    set("nickname", HIY "�����޵�" NOR);
    set("title", HIM "������̽���" NOR);
    set("gender", "����");
    set("shen_type", -1);
    set("age", 42);
    set("long",
	"������������̽������ų����˿ɵУ������һ�ƺ�Ϊ���������ܡ���\n");
    set("attitude", "peaceful");

    set("per", 21);
    set("str", 21);
    set("int", 30);
    set("con", 26);
    set("dex", 30);

    set("chat_chance", 1);
    set("chat_msg", ({
  	"��������̾�˿����������� ���� �ҵ�����....����ô��������,�Һ�\n"
 	"������ ������������������¶������ã��\n",
    }));
    set("inquiry", ([
	"����ͤ"   : "���ֱ���Ұ��˵�����,������ѽ�� \n",
	"��������" : "������ܰ���ȡ�ÿ��������ϲᣬ��һ������л�㡣\n",
    ]));

    set("qi", 4000);
    set("max_qi", 4000);
    set("jing", 1000);
    set("max_jing", 1000);
    set("neili", 4500);
    set("max_neili", 4500);
    set("jiali", 400);

    set("combat_exp", 2500000);
    set("score", 0);

    set_skill("force", 290);	     // �����ڹ�
    set_skill("finger", 290);	    // ����ָ��
    set_skill("unarmed", 290);	   // ����ȭ��
    set_skill("dodge", 300);	     // ��������
    set_skill("parry", 290);	     // �����м�
    set_skill("sword", 290);	     // ��������
    set_skill("pixie-jian", 300);	// ��а����
    set_skill("changquan", 280);	 // ̫�泤ȭ
    set_skill("literate", 120);	  // ����ʶ��
    set_skill("kuihua-xinfa", 290);      // �����ķ�

    map_skill("force", "kuihua-xinfa");
    map_skill("sword", "pixie-jian");
    map_skill("unarmed", "changquan");
    map_skill("dodge", "pixie-jian");
    map_skill("parry", "pixie-jian");

    create_family("�������", 2, "����");

    setup();
    carry_object("/d/fuzhou/obj/xiuhua")->wield();
    carry_object("/d/wanjiegu/npc/obj/qi-dress")->wear();
}

