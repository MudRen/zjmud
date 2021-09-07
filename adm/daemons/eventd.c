// eventd.c

#include <ansi.h>
#include <localtime.h>

inherit F_DBASE;

static string *event_name;      // ϵͳ�����е��¼�
static mapping event_list;      // ���������¼�

void collect_all_event();

void create()
{
	string event;
	object eob;

	seteuid(ROOT_UID);
	set("channel_id", "�¼�����");
	CHANNEL_D->do_channel(this_object(), "sys", "�¼�ϵͳ�Ѿ�������");

	event_name = get_dir(EVENT_DIR + "*.c");
	event_name = map_array(event_name, (: $1[0..<3] :));

	// �������е��¼�
	foreach (event in event_name)
		if (objectp(eob = find_object(EVENT_DIR + event)))
			destruct(eob);

	event_list = ([ ]);
	collect_all_event();
	set_heart_beat(5);      // ÿ��Сʱ����һ��
}

int clean_up()
{
	return 1;
}

string *query_all_event()
{
	return event_name;
}

mapping query_event_list()
{
	return event_list;
}

// EVENT_D����ʱ�ռ����е��¼�
void collect_all_event()
{
	string event;

	foreach (event in event_name)
		(EVENT_DIR + event)->create_event();
}

// �Ǽ���ĳʱ�������¼�
int test(string st, int year, int month, int day, int hour, mixed para)
{
	if (undefinedp(event_list[st]))
		return notify_fail("not found..\n");

	event_list[st] = ({ year, month, day, hour, para });
}

// �Ǽ���ĳʱ�������¼�
int at_when(int year, int month, int day, int hour, mixed para)
{
	object pob;
	int t;
	mixed *lt;

	if (! objectp(pob = previous_object()))
		return 0;

	if (geteuid(pob) != ROOT_UID)
		// Ϊ�˰�ȫ��ֻ�о���ROOT��ݵĶ�����ܹ��Ǽ��¼�
		return 0;

	event_list[base_name(pob)] = ({ year, month, day, hour, para });
}

// �Ǽ���һ��ʱ���Ժ������¼�
// �������Ĳ����Ǹ��������־��һ�����Ե�ʱ��
// ���磺Y = 0 month = 0 day = 1 hour = -5 ��ʾ����5���� 
int at_after(int year, int month, int day, int hour, mixed para)
{
	mixed *lt;

	lt = NATURE_D->query_localtime(time());
	if (year < 0)  year = -year;   else year += lt[LT_YEAR];
	if (month < 0) month = -month; else month += lt[LT_MON] + 1;
	if (day < 0)   day = -day;     else day += lt[LT_MDAY];
	if (hour < 0)  hour = -hour;   else hour += lt[LT_HOUR];
	return at_when(year, month, day, hour, para);
}

// ÿ��Сʱ����һ�Σ�������е��¼�
void heart_beat()
{
	mixed *lt;
	string *ks;
	string event;
	mixed *el;
	int tnow, tt;
	int r;

	lt = NATURE_D->query_localtime(time());
	lt[LT_MON]++;
	tnow = lt[LT_YEAR] * 1000000 +
	       lt[LT_MON] * 10000 +
	       lt[LT_MDAY] * 100 +
	       lt[LT_HOUR];

	ks = keys(event_list);
	foreach (event in ks)
	{
		el = event_list[event];
		tt = el[0] * 1000000 +
		     el[1] * 10000 +
		     el[2] * 100 +
		     el[3];
		if (tnow < tt) continue;

		// ��ȥ������¼� - ������������ڴ���ǰ���
		map_delete(event_list, event);

		// �¼���Ҫ���������ô������
		r = catch(event->trigger_event(el[4],
					       lt[LT_YEAR], lt[LT_MON],
					       lt[LT_MON], lt[LT_MDAY]));
		if (r) log_file("static/event", sprintf("%s event:%s trigger occur an error.\n",
							log_time(), ks));
	}
}
