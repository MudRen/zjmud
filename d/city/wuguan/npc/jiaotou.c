// jiaotou.c ��ݽ�ͷ
inherit NPC;
#include <ansi.h>

void create()
{
        set_name("��ݽ�ͷ", ({ "wuguan jiaotou", "jiaotou"}));
        set("long", "�������Ƹ��Ľ�ͷ�������еĻ����似���㶼��������ѧϰ��\n"+
                "��ѯ��ͷ����ָ��Ϊ��cha jiaotou��\n"+
                "�ӽ�ͷ��ѧϰ���ܵ�ָ��Ϊ��xue jiaotou <������>��\n");
        set("gender", "����");
        set("age", 41);
        set("unique", 1);
         
        set_skill("sword",180);
        set_skill("blade", 180);
        set_skill("whip", 180);
        set_skill("club", 180);
        set_skill("staff", 180);
        set_skill("throwing", 180);

        set_skill("force", 180);
        set_skill("parry", 180);
        set_skill("dodge", 180);

        set_skill("unarmed",180);
        set_skill("cuff", 180);
        set_skill("strike", 180);
        set_skill("finger", 180);
        set_skill("claw", 180);
        set_skill("hand", 180);


        set("jiali", 50);
        set("apply/attack", 30);
        set("apply/defense", 30);
        set("apply/damage", 35);
        set("combat_exp", 200000);
        set("shen_type", 1);
          
        set("chat_chance", 3);
        set("chat_msg", ({
                CYN"��ݽ�ͷ����������Һú���������ʲô�����������ҡ���"NOR"\n",
                CYN"��ݽ�ͷ�������ƣ������ǿɲ�Ҫ͵��Ŷ����Ҽ��Ͱ�����"NOR"\n",
                (: random_move :)
        }));

        setup();
}

void init()
{
        object ob, me;
        me = this_object();
        ::init();
        if (interactive(ob = this_player()) && ob->query_condition("killer")){ 
                command("say �㾹�������ɱ��! \n");
                me->set_leader(ob);
                remove_call_out("kill_ob");
                call_out("kill_ob", 1, ob);
        }
}

int is_apprentice_of(object ob)
{
        return 1;
}

int prevent_learn(object ob, string skill)
{
        return 0;
}

int recognize_apprentice(object ob)
{
        return 1;
}
