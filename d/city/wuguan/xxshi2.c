//xxshi2.c
inherit ROOM;

void create()
{
        set("short", "Ů��Ϣ��");
        set("long", @LONG
����������ڵ���Ϣ�ң����ھ�����ɨ�طǳ��ɾ�����������͸��һ����
�µ���Ϣ��һ�Ŵ��̿�ǽ���ţ����ϵ����˽�����Ϣ���Ѻ���ȥ����Ҳ���ĵ�
�Ҹ�����˯��������
LONG);

        set("exits", ([              
	     "north" : __DIR__"zoulang7",
	]));

        set("sleep_room", 1);

     	set("no_fight", 1);

        setup();
}

void init()
{
        add_action("do_get", "get");        
        add_action("do_get", "drop");
}

int do_get()
{
        write("�ֽ���һЩ���㲻�¾��ѱ����𣿣�\n");
        return 1;
}

