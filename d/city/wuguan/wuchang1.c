//wuchang1.c

#include <ansi.h>
inherit ROOM;
int do_da(string arg);

void create()
{
        set("short", "���䳡");
        set("long", @LONG
�����Ǹ�¶�����䳡���ſ�д��һ�����ӣ�paizi�����ö��������������
���ţ������ڳ��У�����û���˻�ͷ����һ�ۣ����ھ۾�����������Լ��Ĺ�
�򡣵�����һЩ�����õĹ��ߣ�ǽ�߰���һ��ľ׮��zhuang���ͼ��������õ�
ľ�ˣ�muren����
LONG);

        set("exits", ([              
               "east" : __DIR__"wuchang2",
        ]));
	set("no_fight",1);
        set("item_desc", ([
          "zhuang"  :  "һ��ľ׮������Χ��һ���鲼�̶��ڵ��ϣ����˻���(da)������\n",
	  "�����ӡ�" :
		HIY"
������������������������������������
������������������������������������
����������                  ��������
��������   ��  ��  ��  ��   ��������
����������                  ��������     
������������������������������������
������������������������������������"NOR"\n",
		]));

	//set("outdoors","���");
		
        set("objects", ([
                   __DIR__"npc/muren" : 1,
        ]));
	set("action_list", ([
		"��׮":"da zhuang",
	]));
        setup();
}

void init()
{
        add_action("do_da", "da");        
}

int do_da(string arg)
{
        object me;
        int costj, costq;

        me = this_player();
        
        if (me->is_busy()) 
            	return notify_fail("��������æ����!\n");
        if (me->is_fighting())
            	return notify_fail("������ս����,�޷�ר�ĸɻ�!\n");
        if ( !living(me))
            	return notify_fail("�㷢����? \n");        
        if( objectp( me->query_temp("weapon")))
            	return notify_fail("ֻ�п��ֲ��ܴ�ľ׮��\n");
        if (!arg || arg != "zhuang")
      	    	return notify_fail("��Ҫ��ʲô��������\n");

        costj = random((int)me->query("con"));
        costq = random((int)me->query("str"));

        if ((int)me->query("jing") < costj || (int)me->query("qi") < costq){
           	message_vision(HIR"$N��һ�ɣ�һ��С��ײ����ľ׮��!"NOR"\n",me);
           	me->unconcious();
	   	return 1;
	}
        
        me->receive_damage("jing", costj);
        me->receive_damage("qi", costq);       

        message_vision("$Nվ������������ȭ����ľ׮�Դ�������\n", me);

        if ( (int)me->query_skill("cuff", 1) < 20 && random(10)>6 ){
            	write(HIM"���ں�ľ��׮�ĶԴ��������˲��ٻ���ȭ��!"NOR"\n");
            	me->improve_skill("cuff", (int)me->query("int") / 6);
        }
        return 1;
}
