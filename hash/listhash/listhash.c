#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"listhash.h"


/* 创建 */
hashtab *hashtab_create(int size,hash_key_func hash_value,
    	keycmp_func keycmp,hash_node_free_func hash_node_free) 
{
    hashtab *h = NULL;
    int hash_num = 0; // 初始化hash元素的个数

    if(size < 0 || hash_value == NULL || keycmp == NULL) {
        return NULL;
    }

    h = (hashtab *)malloc(sizeof(hashtab));
    if(h == NULL) {
        return NULL;
    }

    h->htables = (hashtab_node**)malloc(size * sizeof(hashtab_node*));
    if(h->htables == NULL) {
        return NULL;
    }

    h->size = size;
    h->hash_value = hash_value;
    h->keycmp = keycmp;
    h->hash_node_free = hash_node_free;
    h->nel = 0;

    for(;hash_num < size; hash_num++) {
        h->htables[hash_num] = NULL;
    }

    return h;
}

/* 销毁 */
void hashtab_destory(hashtab *h) 
{
    int i = 0;
    hashtab_node *cur = NULL;
    hashtab_node *tmp = NULL;

    if(h == NULL) {
        return;
    }

    for (;i < h->size; ++i) {
        cur = h->htables[i];

        while(cur != NULL) {
            tmp = cur;
            cur = cur->next;
            h->hash_node_free(tmp);
        }
    }

    free(h->htables);
    free(h);
    return ;
}

/* 插入 */
int hashtab_insert(hashtab *h ,void *key, void *data) {
    if(h == NULL || key == NULL || data == NULL) {
        return -1;
    }

    unsigned int hvalue = 0;
    hashtab_node *cur = NULL;
    hashtab_node *prev = NULL;
    hashtab_node *tmp = NULL;

    hvalue = h->hash_value(h,key);
    cur = h->htables[hvalue];
    /* hashtable 中的元素在hash链上也是有序的 */
    while(cur != NULL && (h->keycmp(h,key,cur->key) > 0)) {// 找到待插入key的前驱节点
        prev = cur;
        cur = cur->next;
    }

    if(cur != NULL && (h->keycmp(h, key, cur->key) == 0)) { // 当前key存在
        return 1;
    }

    tmp = (hashtab_node *)malloc(sizeof(hashtab_node));
    if(tmp == NULL) {
        return -1;
    }

    tmp->key = key;
    tmp->data = data;

    if(prev == NULL) {
        tmp->next = h->htables[hvalue];
        h->htables[hvalue] = tmp;
    }else {
        tmp->next = prev->next;
        prev->next = tmp;
    }

    h->nel ++;

    // if(h->size * 3 / 4 <= h->nel) {
    //    hashtab_expand(h);
    // }
    return 0;
}

/* 删除 */
hashtab_node *hashtab_delete(hashtab *h, void *key) 
{
    if(h == NULL || key == NULL) {
        return NULL;
    }

    unsigned int hvalue = 0;
    hashtab_node *cur = NULL;
    hashtab_node *prev = NULL;

    hvalue = h->hash_value(h,key);
    cur = h->htables[hvalue];
    while(cur != NULL && (h->keycmp(h,key,cur->key) >= 0) ) {// 找到待删除节点的前驱节点

        if(h->keycmp(h,key,cur->key) == 0) { // 找到匹配的key
            if(prev == NULL) { // 需要删除的key就是hvalue所在hash链上的第一个key
                h->htables[hvalue] = cur -> next;
            }else {
                prev->next = cur->next;
            }
            h->nel --;
            return cur;
        }

        prev = cur;
        cur = cur ->next;
    }


    return NULL;
}

/* 查找 */
void *hashtab_search(hashtab*h,void *key) 
{
    if(h == NULL || key == NULL) {
        return NULL;
    }

    unsigned int hvalue = 0;
    hashtab_node *cur = NULL;

    hvalue = h->hash_value(h,key);
    cur = h->htables[hvalue];
    if(cur == NULL) { // 先确认hash桶是否存在
        return NULL;
    }

    while(cur != NULL) {
        if(h->keycmp(h,key,cur->key) == 0) {
            return cur->data;
        }
        cur = cur ->next;
    }

    return NULL;
}

void hashtab_dump(hashtab *h) 
{
    int i = 0;
    hashtab_node *cur = NULL;

    if(h == NULL) {
        return;
    }

    printf("\r\n----开始--size[%d],nel[%d]------------", h->size, h->nel);
    for(;i< h->size; ++i) {
        printf("\r\n htables[%d]:",i);
        cur = h->htables[i];
        while(cur != NULL) {
            printf("key[%s],data[%s] ", cur->key, cur->data);
            cur = cur ->next;
        }
    }

    printf("\r\n----结束--size[%d],nel[%d]------------", h->size, h->nel);
}

/* 扩容 */
void  *hashtab_expand(hashtab *tmp_h) {
    if(tmp_h == NULL || (tmp_h ->size * 3 / 4 > tmp_h->nel)) {
        return NULL;
    }

    printf("begin expand\n");

    hashtab *new_h = NULL;
    hashtab *h = tmp_h;
    hashtab_node *cur = NULL;
    int i = 0;

    new_h = hashtab_create(h->size * 2, h->hash_value,
                            h->keycmp, h->hash_node_free);

    for (;i < h->size; ++i) {
        cur = h->htables[i];
        while(cur != NULL) {
            hashtab_insert(new_h, cur->key, cur->data);
            cur = cur->next;
        }
    }

    printf("before destory\n");
    hashtab_destory(tmp_h);
    printf("end destory\n");
    // hashtab_dump(new_h);
    tmp_h = new_h;

    return NULL;
}

struct test_node
{
    /* data */
    char key[30];
    char data[30];
};

unsigned int simple_hash(const char *str)
{
	register unsigned int hash = 0;
	register unsigned int seed = 131;

	while(*str)
	{
		hash = hash*seed + *str++;
	}

	return hash & (0x7FFFFFFF);
}

int hashtable_hvalue(hashtab *h, const void *key) 
{
    return simple_hash(key) % h->size;
}

int hashtable_compare(hashtab*h, const void *key1, const void *key2)
{
    return strcmp(key1, key2); 
}

void hashtable_node_free(hashtab_node *cur) 
{
    struct test_node *tmp = NULL;
    tmp = container(cur->key,struct test_node,key);

    free(tmp);
    free(cur);
}

int main ()
{
	
	int res = 0;
	char *pres = NULL;
	hashtab_node * node = NULL;
	struct test_node *p = NULL;
    hashtab *h = NULL;

	h = hashtab_create(6,hashtable_hvalue,hashtable_compare,hashtable_node_free);// 创建一个hash桶大小为5的hash表
    assert(h!= NULL);
	while(1)
	{
		p = (struct test_node*)malloc(sizeof(struct test_node));
		assert(p != NULL);
		printf("\r\n 输入key  value，输入\"quit\"退出");
        scanf("%s",p->key);
		scanf("%s",p->data);

		if(strcmp(p->key,"quit") == 0)
		{
			free(p);
			break;
		}

        res = hashtab_insert(h,p->key,p->data);
		if (res != 0)
		{
			free(p);
			printf("\r\n key[%s],data[%s] insert failed %d",p->key,p->data,res);
		}
		else
		{
			printf("\r\n key[%s],data[%s] insert success %d",p->key,p->data,res);
		}
	}

	hashtab_dump(h);

	while(1)
	{
		p = (struct test_node*)malloc(sizeof(struct test_node));
		assert(p != NULL);
		printf("\r\n 请输入key 查询value的数值，当可以等于\"quit\"时退出");
        scanf("%s",p->key);

		if(strcmp(p->key,"quit") == 0)
		{
			free(p);
			break;
		}
        pres = hashtab_search(h,p->key);
		if (pres == NULL)
		{
			printf("\r\n key[%s] search data failed",p->key);
		}
		else
		{
			printf("\r\n key[%s],search data[%s] success",p->key,pres);
		}
		free(p);
	}
	hashtab_dump(h);
	while(1)
	{
		p = (struct test_node*)malloc(sizeof(struct test_node));
		assert(p != NULL);
		printf("\r\n 请输入key 删除节点的数值，当可以等于\"quit\"时退出");
        scanf("%s",p->key);

		if(strcmp(p->key,"quit") == 0)
		{
			free(p);
			break;
		}
        node = hashtab_delete(h,p->key);
		if (node == NULL)
		{
			printf("\r\n key[%s] delete node failed ",p->key);
		}
		else
		{
			printf("\r\n key[%s],delete data[%s] success",node->key,node->data);
		    h->hash_node_free(node);
		}
		free(p);
	    hashtab_dump(h);
	}

	hashtab_destory(h);

	return 0;

}