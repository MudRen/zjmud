// Room: /city/bocai.c 
#include <room.h> 
inherit CREATE_CHAT_ROOM; 
	
int is_chat_room() { return 1; } 
	
void create() 
{ 
	set("short", "���²�����"); 
	set("long", @LONG 
����һ�����ܵĵ��²����ݣ��Ե�ǰ�ĸ������ű�����������
�ʡ���ӭ������ʿ����һ��������ǽ�Ϲ���һ������(paizi)�� 
LONG 
	); 
	set("no_fight", 1); 
	set("no_sleep_room", 1); 

	set("item_desc", ([ 
		"paizi" : "��ע��(news)�е�ǰ������������ʣ�Ȼ����"
			  "��ֵ��ʦ��ϵ���ɵ�ֵ��ʦ����Ǯ�������԰�"
			  "��ע����ע��ӻ���ѡ�֣��Լ���ע����"
			  "������ϵ��ֵ��ʦ�������󼴷��š�\n", 
	])); 
	set("exits", ([ 
		"up" : __DIR__"chaguan", 
	])); 
	setup(); 
} 
